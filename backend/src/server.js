const cors=  require('cors');
const express = require('express');
const routes = require('./routes');
const path = require('path');

const app = express();
//comando para achar o ip   
//  ifconfig
app.use(express.urlencoded());
app.use(express.json()); 

app.use(cors());
app.use(express.json());
app.use(routes);
app.listen(3333);
