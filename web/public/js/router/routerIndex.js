import React,{Component} from "react";
import { HashRouter as Router,Route} from 'react-router-dom';
import ViewIndex from "@view/index";
import ViewTable from "@view/table";

class RouterIndex extends Component{
    render(){
       return <div>
            <Route exact path="/index" component={ViewIndex} />
            <Route exact path="/table" component={ViewTable} />
        </div>
    }
}
export default RouterIndex;