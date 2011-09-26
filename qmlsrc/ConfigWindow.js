
var cfg =  {
    options: false,
    owner: false,

    show: function() {
              this.options.forEach(function(elem) {
                          console.log(elem)
                      })
          },
    clear: function() {
               this.options = new Array();
           },
    addOpt: function(i, t, q) {
                if (!this.options)
                    this.options = new Array()
                this.options.push({ identifier:i, type:t, question:q })
            }
}
