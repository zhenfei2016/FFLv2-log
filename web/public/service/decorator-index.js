import axios from "axios";
let Axios,$axios,success,error;
$axios = axios.create({
    headers: {
        'Accept':'application/json',  
        'Content-Type':'application/json'
        }
})
 success=(da)=>{
     
     let {data}=da;
    return data;
}
 error=(e)=>{
     
  return Promise.reject(e)
}
export default Axios=(target,name,discriptor)=>{
   Object.assign(target.prototype,{$axios,success,error})
    return target;
}