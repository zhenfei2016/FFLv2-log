import React,{Component,Children} from "react";
import {Provider} from "react-redux";
import { HashRouter as Router,Route} from 'react-router-dom';
import RouterIndex from "@js/router/routerIndex";
import store from "@js/redux";
class Prouter extends Component{
    
    render(){
       
        return <Provider store={store}> 
                     <Router>
                        <RouterIndex/>
                    </Router> 
               </Provider>
    }
}
export default Prouter;