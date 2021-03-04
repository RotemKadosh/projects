# README file:
## target:
This program receive input of a JSON file containing list of
virtual machines under the tag of "vms"
and a list of firewall rules under the tag of "fw_rules".

on First run this program creates an SQLite DB in CWD and loads the input file to this DB. the DB schema is described at the end of this file.

the program create two REST endpoint services:
1. /attacks - receive vm_id as arguments in format of:
              /attack?vm_id=vm-a211de
              the output is a list of all other 
              vm_id that can access this machine
2. /stats - output the attacks service statistics: 
            1. amount of vm in the cloud 
            2. amount of requests to attacks service that been made
            3. average process time of requests of attacks service 

# configuration:
this program written on linux (ubuntu 18.4) in python 2.7 using flask framework
to download python:  
    ```https://www.python.org/downloads/``
for flask:
   ``` https://flask-restful.readthedocs.io/en/latest/quickstart.html``
for flask_restful: 
    ```pip install flask_restfull```

after setting the flask virtualenv.

run the script service_bd.py attached with the input file:
    ```python service_db.py input-0.json```


# personal note:
it was the first time for me to build a​ ​REST service endpoints,
so for me it was great opportunity to learn new things about REST, networking.
i also got the chance to work with python  and sql for the first time in a long while which was real fun.
im sure this program has ways to improve, like making configuration file to adjust db location and other settings, or to make some authentication for the services.

# DB Scheme:

Table vms:
id TEXT PRIMARY KEY,
name TEXT

Table rules:
rule_name TEXT PRIMARY KEY,
source_tag TEXT NOT NULL REFERENCES vm_tags (name),
dest_tag TEXT NOT NULL REFERENCES vm_tags (name)

Table vm_tags:
vm_id TEXT NOT NULL,
name TEXT NOT NULL, 
FOREIGN KEY (vm_id) REFERENCES vms (id)

Table requests:
processing_time FLOAT NOT NULL