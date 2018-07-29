
import React, { Component } from "react";
import {connect} from "react-redux";
import {mixin} from "@js/tools";
import controllerTable from "./controller-table";
import actionTable from "./action-table";
const mapStateToProps=(state)=>{

    return {storeTabel:state.storeTable}
}
const mapDispatchToProps=(dispatch)=>{
   return {
        onLoad(callback){ callback(dispatch) }
   }
}
@connect(mapStateToProps,mapDispatchToProps)
@mixin(controllerTable,actionTable)

class ViewTable extends Component{
    constructor(props, context){
        super(props, context);
        this.dispatch=null;
        this.local={
            list:{} //数据
           
        }
        this.state={
            all:false //是否显示全部数据
        }
       
    }
    componentDidMount(){
        this.props.onLoad(dispatch=>this.dispatch=dispatch); 
        this.init();
    }
    init(){
        this.T_getWX();
    }
    render(){
        let {storeTabel} = this.props
        //if(!storeTabel){ return <div>加载中。。。</div>}
       let {list} =  storeTabel.data;
       console.log(this.state)
       if(!this.state.all){
          list = eval(list).slice(-10);
       }
        return  <section>
                <lable>显示全部：<input type="checkbox" onChange ={this.ACheckboxChange.bind(this)} /></lable>
                <ul>
                    {
                       list.map((da,ind)=>{
                           return <li key={ind}>{da["id"]||"null"}</li>
                       }) 
                    }
                </ul>
        </section>
    }
}

export default ViewTable;