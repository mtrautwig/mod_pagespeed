(function(){var c=function(a,b,d){if(a.addEventListener)a.addEventListener(b,d,!1);else if(a.attachEvent)a.attachEvent("on"+b,d);else{var e=a["on"+b];a["on"+b]=function(){d.call(this);e&&e.call(this)}}};window.pagespeed=window.pagespeed||{};var f=window.pagespeed,g=function(){this.a=this.c=!1};g.prototype.b=function(a){for(var b=0;b<a.length;++b){var d=a[b].getAttribute("pagespeed_high_res_src");d&&a[b].setAttribute("src",d)}};g.prototype.replaceElementSrc=g.prototype.b;
g.prototype.f=function(){if(this.c)this.a=!1;else{var a=document.body,b,d=0,e=this;"ontouchstart"in a?(c(a,"touchstart",function(){b=Date.now()}),c(a,"touchend",function(a){d=Date.now();(null!=a.changedTouches&&2==a.changedTouches.length||null!=a.touches&&2==a.touches.length||500>d-b)&&h(e)})):c(window,"click",function(){h(e)});c(window,"load",function(){h(e)});this.c=!0}};g.prototype.registerLazyLoadHighRes=g.prototype.f;var h=function(a){a.a||(a.d(),a.a=!0)};
g.prototype.d=function(){this.b(document.getElementsByTagName("img"));this.b(document.getElementsByTagName("input"))};g.prototype.replaceWithHighRes=g.prototype.d;f.e=function(){f.delayImages=new g};f.delayImagesInit=f.e;})();