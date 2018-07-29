import * as service from "@service/service-index.js";
let number=0;
export default {
  //我在dev上的注释上的注释
  async C_getData(data){
       let da =await service.getData();
       return da
         // this.local.list = list;
        //  return list
     },
  async C_setTimeline({page=0,count=10}={}){
       let data =await this.C_getData({page,count});
           data = data.filter(da=>(da["id"]!=""&&da["node"]!=""&&da["procBeginTime"]!=""&&da["procEndTime"]!=""));
           
       let sortlist = [...new Set(data.map(arg=>parseInt(arg.procBeginTime)).concat(data.map(arg=>parseInt(arg.procEndTime))).sort())];
       // console.log(sortlist);
        this.local.timeLine=sortlist;
           this.C_filterList(data);//过滤数据
           this.C_filterNode(data);//过滤数据
           this.C_dispatch();  //发布
     },
     C_filterNode(da){
       let data =  da.map(arg=>arg.id);
       this.local.tools.souceId=["全部",...new Set(data)];
       
     },
     C_filterList(da){
       let list = {};
           da.forEach(arg => {
               list[arg.node]=list[arg.node]||[];
               
               list[arg.node].push(arg);
           });
           this.local.list = list;
          // console.log(list);
     },
     C_dispatch(){
          let {timeLine,list,tools}=this.local;
          this.dispatch({
            type:"storeIndex",
            data:{ list,timeLine,showId:tools.showId}
          })
     }
   

   
   
}