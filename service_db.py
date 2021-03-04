from flask import Flask
import json
from flask_restful import Resource, Api, reqparse
import sys 
from timeit import default_timer as timer
import sqlite3
from sqlite3 import Error
import logging

app = Flask(__name__)
@app.route('/http://localhost/api/v1')





class Stats(Resource):
    def get(self):
        path = './service.db'
        db = create_connection(path)
        stats= {
            "average_request_time": execute_read_query(db, "SELECT ROUND(AVG(processing_time),3) FROM requests")[0], 
            "request_count":  execute_read_query(db, "SELECT COUNT(*) FROM requests")[0],
            "vm_count": execute_read_query(db, "SELECT COUNT(*) FROM vms")[0]
        }
        return stats

class Attacks(Resource):
    
    def get(self):
        start = timer()
        db_path = './service.db'
        parser = reqparse.RequestParser()
        parser.add_argument('vm_id', required=True)
        args = parser.parse_args()
        db = create_connection(db_path)
        
        
        accessible = execute_read_query(db,"SELECT * FROM vms WHERE id == '""" + args['vm_id'] + """'""")
        if(len(accessible) == 0):
            InsertRequestToDb(db, start)
            return "VM Not Found"
        
        query = """
            SELECT DISTINCT t.vm_id as id
            FROM vm_tags as t
            WHERE t.name IN (
                            SELECT r.source_tag as tag_name
                            FROM rules as r JOIN (
                                                SELECT name
                                                FROM vm_tags
                                                WHERE vm_id == '""" + args['vm_id'] + """'
                                                ) as tags
                            ON r.dest_tag == tags.name
                            )
                AND t.vm_id != '""" + args['vm_id'] + """'
        """
        attackers = execute_read_query(db, query)
        InsertRequestToDb(db, start)
        if(len(attackers) == 0):
            return "This VM is inaccessible"
        return attackers

def execute_query(connection, query):
    cursor = connection.cursor()
    try:
        cursor.execute(query)
        connection.commit()
    except Error as e:
        logging.error("error occurred with query: " + query)
    cursor.close()

def execute_read_query(connection, query):
    cursor = connection.cursor()
    result = None
    try:
        cursor.execute(query)
        result = cursor.fetchall()
        return result
    except Error as e:
        logging.error("error occurred with " + query)

def create_connection(path):

    connection = None
    try:
        connection = sqlite3.connect(path)
    except Error as e:
        logging.error("Connection error occurred")
    return connection

def InsertRequestToDb(db, start):
    time = timer() - start
    execute_query(db, "INSERT INTO requests VALUES ('" + str(time) +"')" )

def LoadVmsTable(db_connection, path):
    with open(path) as f: 
        data = json.load(f)
    vm_list = data['vms']
    query = "insert into vms values "
    for vm in vm_list:
        vals = "('" + vm['vm_id'] + "', '" + vm['name'] + "')"
        execute_query(db_connection ,query + vals)

def LoadTagTable(db_connection, path):
    with open(path) as f: 
        data = json.load(f)
    vm_list = data['vms']
    query = "insert into vm_tags values "
    for vm in vm_list:
        for tag in vm['tags']:
            vals = "('" + vm['vm_id'] + "', '" + tag + "')"
            execute_query(db_connection ,query + vals)

def LoadRulesTable(db_connection, path):
    with open(path) as f: 
        data = json.load(f)
    rules_list = data['fw_rules']
    query = "insert into rules values "
    for rule in rules_list:
        vals = "('" + rule['fw_id'] + "', '" + rule['source_tag'] + "', '" + rule['dest_tag'] + "')"
        execute_query(db_connection ,query + vals)

def LoadInputFileToDb(db_connection, path):
    LoadVmsTable(db_connection, path)
    LoadTagTable(db_connection, path)
    LoadRulesTable(db_connection, path)
    pass

def CreateVmTable(db):
    drop_query = "DROP TABLE "
    execute_query(db, drop_query + "vms")
    create_vm_query = """
    CREATE TABLE IF NOT EXISTS vms (
    id TEXT PRIMARY KEY,
    name TEXT
    );
    """
    execute_query(db, create_vm_query)

def CreateVmTagsTable(db):
    drop_query = "DROP TABLE "
    execute_query(db, drop_query + "vm_tags")
    create_tag_query = """
    CREATE TABLE IF NOT EXISTS vm_tags (
    vm_id TEXT NOT NULL,
    name TEXT NOT NULL, 
    FOREIGN KEY (vm_id) REFERENCES vms (id)
    );
    """
    execute_query(db, create_tag_query)

def CreateRuleTable(db):
    drop_query = "DROP TABLE "
    execute_query(db, drop_query + "rules")
    create_rules_query = """
    CREATE TABLE IF NOT EXISTS rules (
    rule_name TEXT PRIMARY KEY,
    source_tag TEXT NOT NULL REFERENCES vm_tags (name),
    dest_tag TEXT NOT NULL REFERENCES vm_tags (name)
    );
    """
    execute_query(db, create_rules_query)

def CreateRequestTable(db):
    drop_query = "DROP TABLE "
    execute_query(db, drop_query + "requests")
    create_request_query = """
    CREATE TABLE IF NOT EXISTS requests (
    processing_time FLOAT NOT NULL
    );
    """
    execute_query(db, create_request_query)

def CreateDB(path):
    db = create_connection(path)
    CreateVmTable(db)
    CreateVmTagsTable(db)
    CreateRuleTable(db)
    CreateRequestTable(db)
    return db


api = Api(app)
api.add_resource(Attacks, '/attacks')
api.add_resource(Stats, '/stats')


if __name__ == '__main__':
    arguments = sys.argv
    arg_len = len(arguments)
    if (arg_len <= 1 or arg_len > 2):
        logging.error("too few or too many arguments, insert only input file path")
    
    path  = arguments[1]
    db = CreateDB('./service.db')
    LoadInputFileToDb(db, path)
    app.run()  

