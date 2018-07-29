import {connect} from "react-redux";
let myconnect;
const mapStateToProps=(state)=>{
    
    return {storeIndex:state.storeIndex}
}
const mapDispatchToProps=(dispatch)=>{
   return {
        onLoad(callback){ callback(dispatch) }
   }
}
//@connect(mapStateToProps,mapDispatchToProps)
export default myconnect=(target,name,discription)=>{
    debugger
     return target;
}
//@connect(mapStateToProps,mapDispatchToProps)