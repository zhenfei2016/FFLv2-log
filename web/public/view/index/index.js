import React, { Component } from "react";
import controllerIndex from "./controller-index";
import actionIndex from "./action-index";
import {connect} from "react-redux";
import {mixin,time} from "@js/tools";

import ("@view/index/css/index.scss");
 const mapStateToProps=(state)=>{
    
    return {storeIndex:state.storeIndex}
}
const mapDispatchToProps=(dispatch)=>{
   return {
        onLoad(callback){ callback(dispatch) }
   }
}
@connect(mapStateToProps,mapDispatchToProps)
@mixin(controllerIndex,actionIndex)
class VIewIndex extends Component{
    constructor(props, context){
        super(props, context);
        this.dispatch=null;
        this.local={
            list:{}, //数据
            tools:{
                souceId:[],
                showId:-1,
                current:0,
                color:[]
            },
            timeLine:[], //时间线
            timeLineLi:{
                width:200,
                height:40
            },
            blockLi:{
                warpWidth:0,//总宽
                width:200,//单元格宽
            }
        }
       
    }
    componentDidMount(){
        this.props.onLoad(dispatch=>this.dispatch=dispatch);
        this.init();//初始化
      
       
    }
    componentWillReceiveProps(next){
       
    }
    componentWillUnmount(){
        this.A_EventRemove();
    }
     init(){
         this.C_setTimeline();//初始化生成线阵
         this.A_EventToutch();//绑定touch
    }
    getProsition=(da,step)=>{
         let {procBeginTime,procEndTime}=da;
         let start = this.local.timeLine.indexOf(parseInt(procBeginTime));
         let end = this.local.timeLine.indexOf(parseInt(procEndTime));

             return {
                 start:start*step,
                 end:end*step
             }
    }
    createTimeLineLi=(da)=>{
        
       let dom=[],num=0,h=40,l=10;
       let {width} = this.local.blockLi;
       let color = this.setColor();
       let {showId}=this.props.storeIndex.data;
       //console.log(showId);
           for(let li in da){
               
              //da[li][symbol]=li.toString;
              dom.push(<li key={num} index={num} style={{width:width+"px",left:num*width+"px"}}>
                  <h6 className="title">{li}</h6>
                  <div className="content">
                  {
                     da[li].map((arg,ind)=>{
                         let {start,end}=this.getProsition(arg,40);
                       //  console.log((end-start));
                         return <span 
                                    key={ind} className="line" 
                                    style={{opacity:`${showId<0? 1:arg.id==showId? 1:0.1}`,top:start+"px",backgroundColor:`${color[num]}`,height:Math.abs(end-start)+"px",left:(ind*2)+"px"}}
                                ><i className="nodeId">{arg.id}</i></span>
                     })
                  }
                  </div>
              </li>);
               num+=1; 
           }
           
        return dom
    }
    setColor=()=>{
        if(this.local.tools.color.length){ return this.local.tools.color}
        let color = [
                     "#ABF000","#8DB42D","#6F9C00","#C2F83E","#D0F86F",
                     "#00A876","#207E62","#006D4C","#35D4A4","#5FD4B1",
                     "#FFD600","#BFA830","#A68B00","#FFE040","#FFE873",
                     "#C50080","#94256D","#800053","#E238A7","#E266B7"
                    ]
      
       
        for(let i = 0 ; i<color.length;i++){
            let num = Math.floor(Math.random()*color.length);
            let current =color[i];
            color[i]=color[num];
            color[num]=current;
        }
        this.local.tools.color=color;
        return color;
    }
    render(){
        let {storeIndex} = this.props
        let {list={},timeLine=[]}=storeIndex.data;
        let {height:h,width:w}=this.local.timeLineLi;
        let {width}=this.local.blockLi;
        this.local.blockLi.warpWidth = list.length*this.local.timeLineLi.width;
        return  <section>
                   <div className="timeTools">
                        <label>选择重点显示ID：</label>
                        <select onChange={this.A_ToolsChange.bind(this)}>
                            {
                                this.local.tools.souceId.map((da,ind)=>{
                                    return <option key={ind} value={da=="全部"? -1:da }>{da}</option>
                                })
                            }
                        </select>
                        <p>
                            <label>选择工具：</label>
                            <label>卡尺 <input type="checkbox"  /></label>
                        </p>
                        
                   </div>
                    <article className="timeLine">
                    <ol className="timeLineBox" style={{top:h+"px",left:"10px",height:timeLine.length*h+"px",width:"80px"}}>
                        {
                        timeLine.map((da,ind)=>{
                            
                            return <li style={{top:h*ind+"px",height:h+"px"}} key={ind}>{ da  }</li>
                        })
                        }
                    </ol>
                    <ul className="timeLineBlock" style={{left:80+20+"px",top:"10px",height:timeLine.length*h+"px",width:this.local.blockLi.warpWidth+"px"}}>
                            {
                                this.createTimeLineLi(list)
                            
                            }
                    </ul>
                    
                </article>
        </section>
    }
}

export default VIewIndex;
//export default connect(mapStateToProps,mapDispatchToProps)(VIewIndex);