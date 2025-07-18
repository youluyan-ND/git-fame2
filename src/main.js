import Vue from "vue";
import App from "./App.vue";

// 加载基础ElementUI
import ElementUI from "element-ui";
Vue.use(ElementUI);
import "../package/theme/element-variables.scss";

import hljs from "highlight.js";
import "highlight.js/styles/atom-one-dark-reasonable.css";
Vue.use(hljs.vuePlugin);

import MyPD from "../package/index.js";
Vue.use(MyPD);
import "../package/theme/index.scss";

import "bpmn-js/dist/assets/diagram-js.css";
import "bpmn-js/dist/assets/bpmn-font/css/bpmn.css";
import "bpmn-js/dist/assets/bpmn-font/css/bpmn-codes.css";

// import "bpmn-js-properties-panel/dist/assets/bpmn-js-properties-panel.css"; // 右边工具栏样式

new Vue({
  render: h => h(App)
}).$mount("#app");
