let test,action;
    test=(target,name,des)=>{ 
        Object.assign(target,action);
        console.log("target",target)
        return target
    }
    
    action={

        init(){
            console.log(this);
        }
    }
export default test;