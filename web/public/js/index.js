
import React, { Component } from "react";
import reactDom from 'react-dom';
import Prouter from "@js/router";
import("@css/index.scss");
class Index extends Component{
    state={

    }
    componentDidMount(){
      
     }
    render(){
        return <section>
           <Prouter />
        </section>
    }
}

reactDom.render(<Index />,document.querySelector("#Router"))