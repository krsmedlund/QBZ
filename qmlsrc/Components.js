
var componentContainer = {
    componentList: {},
    addNode: function(name)
             {
                if (!this.componentList[name]) {
                    var comp = Qt.createComponent(name + ".qml")
                } else {
                    var comp = this.componentList[name]
                }
                if (comp.status == Component.Ready) {
                    this.componentList[name] = comp
                    var inst = comp.createObject(page, {x:"200", y:"250"})
                } else {
                    console.log("error adding component "    + comp.errorString())
                }
                return inst
            },
    onConfigComplete: function() {},
    onConfigCancel: function() {},
};

