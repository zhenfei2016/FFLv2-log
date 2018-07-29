import React,{Component,Children} from "react";
import test from "./test";
class Demo extends Component{
    componentDidMount(){
       console.log("props",this.props);
       this.test();
       console.log(this);
    }
    @test
    test(){
        let d = this.props.data;
        Children.map(this.props.children,(el)=>{
            Object.seal(el.props);
            console.log(Object.isSealed(el.props));
          
        })        
    }
    render(){
      //  this.props.children.props["data"]=this.props.data;
       
       return <div>
           {this.props.children}
       </div>
    }
}
export default Demo;