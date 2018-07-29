import * as service from "@service/service-index.js";
export default{
    T_getWX(){
        let th = this;
        

        service.getTestTW()
        .then(da=>{
            let {storeTabel} = th.props;
            let {list} =  storeTabel.data;
                list=[...list,...da];
                
           th.dispatch({
             type:"storeTable",
             data:{ list}
           })

           setTimeout(()=>{
            th.T_getWX();
           },2000);
        });

     }
}