'use strict';

const fs = require('fs');

let rawdata = fs.readFileSync('student.json');
let student = JSON.parse(rawdata);
student["add"] = 20;
student["car"] = "Toyota";
let data = JSON.stringify(student);
fs.writeFileSync('student.json', data);
