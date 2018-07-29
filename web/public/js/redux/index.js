import {createStore,combineReducers} from "redux";
import * as list from "./list"; 
let reducerlist = list;
let combinereducers = combineReducers(reducerlist);
let reducer = combinereducers;
let store = createStore(reducer);
export default store;


