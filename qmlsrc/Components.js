
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
                    var inst = comp.createObject(page, {x:"100", y:"100"})
                    inst.name = name
                    inst.showConfigWindow()
                } else {
                    console.log("error adding component "    + comp.errorString())
                }
            }
};

