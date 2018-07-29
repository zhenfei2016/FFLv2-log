let opt = {
    startx:0,
    starty:0,
    x:0,y:0, //移动坐标
    start:false, //是否移动
    ele:null,  //移动父元素
    x1:0,y1:0, //点击title内坐标为止
    left:0 ,   //父元素距左侧为止
    index:null
}
export default{
  
    A_EventToutch(){
        
        let ele = document.querySelector(".timeLineBlock");
            ele.addEventListener("mousedown",this.Private_Mousedown.bind(this),false);
            window.addEventListener("mousemove",this.Private_Mousemove.bind(this),false);
            window.addEventListener("mouseup",this.Private_Mouseup.bind(this),false);
    },
    Private_Mousedown(event,th){
        let tar = event.target;
        let ele = document.querySelector(".timeLineBlock");
        let left = ele.getBoundingClientRect().x;
        
        
        if(tar.className==="title"){
            let {x,y}=tar.getBoundingClientRect();
            let {layerX,layerY}=event;
            let li=tar.parentNode;
            opt.index = li.getAttribute("index")
            let startx = opt.index*this.local.blockLi.width;
            Object.assign(opt,{startx,x,y,start:true,ele:li,x1:layerX,y1:layerY,left});
            document.body.classList.add("noselect");
        }
    },
    Private_Mousemove(event,th){
     
        let {x1,ele,start,left}=opt;
        let {pageX}=event;
        if(!start){return}
        opt.x = pageX-x1-left;
        Object.assign(ele.style,{left:opt.x+"px",zIndex:100})
        this.Private_Dommove();
        //console.log(opt.x);
    },
    Private_Mouseup(event,th){
        opt.start=false;
        let left = this.Private_checkPostion();
        //Object.assign(opt.ele,{left:left+"px",zIndex:1})
         opt.ele.style.left = left+"px";
         opt.ele.style.zIndex=1;
        document.body.classList.remove("noselect");
        
    },
    A_EventRemove(){
        let ele = document.querySelector(".timeLineBlock");
        let th = this;
        ele.removeEventListener("mousedown",th.Private_Mousedown,false);
        window.removeEventListener("mousemove",th.Private_Mousemove,false);
        window.removeEventListener("mouseup",th.Private_Mouseup,false);
    },
    Private_checkPostion(){ 
       
        let {wrapWidth,width} = this.local.blockLi;
        let {startx,x,ele} = opt;
       
         if(Math.abs(startx-x)<width){
           return startx
         }else{

         }
          
    },
    Private_Dommove(){
        let {x,ele} = opt;
        let {width} = this.local.blockLi;
        let index = Math.ceil((x+width/2)/width);
        let {storeIndex} = this.props
        let {list}=storeIndex.data;
    
        if(index!=parseInt(opt.index)+1){
            console.log(list);
        }
    },
    A_ToolsChange(ev){
        let el =ev.target;
        let value = el.value;
        let {timeLine,list}=this.local;
        this.dispatch({
            type:"storeIndex",
            data:{ showId:value,timeLine,list}
        })
    }


}
 