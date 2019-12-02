import React, { Component } from 'react';
import { Button,StyleSheet, Text, View, FlatList, TouchableOpacity } from 'react-native';
import Axios from 'axios';

/**
 * 
 * npm install
 * npm run android
 * npm run start
 * 
 * https://facebook.github.io/react-native/docs/getting-started
 */
const styles = StyleSheet.create({
  bigBlue: {
    fontWeight: 'bold',
    fontSize: 22,
    padding: 10
  },
  red: {
    color: 'red',
    width: 'auto',
    height: 100,
    justifyContent: 'center',
    alignItems: 'center',
    fontSize: 50,

  },
  green: {
    color: 'green',
    width: 'auto',
    height: 100,
    justifyContent: 'center',
    alignItems: 'center',
    fontSize: 50,

  },
});


function wait(timeout, callback) {
  return new Promise(resolve => {
    setTimeout(resolve, timeout);
  });
}

export default class LotsOfStyles extends Component {

  constructor(props) {
    super(props);
    this.state = {
      leitura: '',
      historico: []
    };
  }

  componentDidMount(prevProps) {
    this.handleSeach();
  
  }

  handleSeach() {
    Axios.get('http://192.168.122.1:3333/')
      .then((res, req) => {
        let history = res.data.historico
        let leitura = history[0].leitura;
        let historico = res.data.historico;

        this.setState({
          leitura: leitura,
          historico: historico
        })
      }).then(()=>{
        setTimeout( () =>  this.handleSeach(), 10000);
      })
  }
  
  alertUmidade(value){
    if(value < 5){
      return {
        color: 'red',
        width: 'auto',
        height: 100,
        justifyContent: 'center',
        alignItems: 'center',
        fontSize: 50,
    
      }
    }else{
      return {
        color: 'green',
        width: 'auto',
        height: 100,
        justifyContent: 'center',
        alignItems: 'center',
        fontSize: 50,
    
      }

    }
  }

  render() {
    return (
      <View>

        <Text style={this.alertUmidade(this.state.leitura)} > Umidade {this.state.leitura}% </Text>
        <FlatList
          style={{ paddingBottom: 41, height: 500}}
          data={this.state.historico}
          keyExtractor={item => item.hora}
          renderItem={({ item }) =>
            <TouchableOpacity
            >
              <View  >
                <Text style={styles.bigBlue} >Data:{item.data}-{item.hora} - Umid.:{item.leitura}%</Text>
              </View>
            </TouchableOpacity>}
        />
        <Button
        style={{height: 80}}
        onPress={() => {
          this.handleSeach()
        }}
        title="Press Me"
        />
      </View >
    );
  }
}