const express = require('express');
const multer = require('multer');
const MainController = require('./controllers/MainController');
const routes = express.Router();

routes.get('/',MainController.index);
routes.post('/leitura',MainController.store);


module.exports = routes