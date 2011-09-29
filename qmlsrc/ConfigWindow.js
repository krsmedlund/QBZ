
var cfg =  {
    "options": [{"name": "default"}],
    "owner": false,

    "show": function() {
              cfg.options.forEach(function(elem) {
                          //console.log(elem)
                      })
          },
    "clear": function() {
                 cfg.options = [{"name": "default"}]
           },

    "addOpt": function(i, t, q) {
                cfg.options.push({"name":"kaka", "identifier":i, "type":t, "question":q })
            }
}
