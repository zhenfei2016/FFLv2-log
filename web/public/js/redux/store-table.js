
let db = {
    "type":"storeTable",
    "data":{
        "list":[],
    }
   }
   export let storeTable=(state=db,action)=>{
      let {data,type} = action;
      
       if(type=="storeTable"){
           return Object.assign({},state,action)
       }
       return state;
   }