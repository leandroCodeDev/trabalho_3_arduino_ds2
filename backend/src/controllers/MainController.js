const moment = require('moment');
const bodyParser = require('body-parser');


var lei = {'leitura': '-13' };

var leituras = [];

module.exports = {

    async index(req, res) {
        let data = {leitura:lei, historico: leituras};
        return res.json(data)
    },

    async store(req, res) {

        lei.leitura = req.body.leitura;
        lei.date = moment();

        console.log(req.body);
        leituras.unshift({'leitura':req.body.leitura, 'data':moment().format("DD/MM/YY"), 'hora':moment().format("HH:mm:ss")})
        
        return res.json(true)
    },

}