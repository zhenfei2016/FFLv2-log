export let mixin=(...arg)=>{
 
   return (target,name,descriptor)=>{
     Object.assign(target.prototype,...arg);
   }
}
export let time=(num,str="yyyy-MM-dd hh:mm:ss")=>{
       let d = new Date(num);
       return str.replace(/yyyy/ig,d.getFullYear())
                 .replace(/MM/ig,d.getMonth())
                 .replace(/dd/ig,d.getDate())
                 .replace(/hh/ig,d.getHours())
                 .replace(/mm/ig,d.getMinutes())
                 .replace(/ss/ig,d.getSeconds())
}
export let number=(taget,name,descriptor)=>{
  
}

Date.prototype.format=function(str="yyyy-MM-dd hh:mm:ss"){
   if(!this){return ""}
    
   let yyyy=this.getFullYear(),MM=this.getMonth()+1,dd=this.getDate(),hh=this.getHours(),mm=this.getMinutes(),ss=this.getSeconds()
  return str.replace(/yyyy/,yyyy)
            .replace(/MM/,MM<10? '0'+MM:MM)
            .replace(/dd/,dd<10? '0'+dd:dd)
            .replace(/hh/,hh<10? '0'+hh:hh)
            .replace(/mm/,mm<10? '0'+mm:mm)
            .replace(/ss/,ss<10? '0'+ss:ss)
}
Object.defineProperty(Object.prototype,"length",{
  get(){
    let th = this;
        return Object.keys(this).length
  }
})
