
let db = {
 "type":"storeIndex",
 "data":{
     "list":[],
     "show":true,
     "timeLine":[],
     "showId":-1
 }
}
export let storeIndex=(state=db,action)=>{
   let {data,type} = action;
    if(type=="storeIndex"){
        return Object.assign({},state,action)
    }
    return state;
}