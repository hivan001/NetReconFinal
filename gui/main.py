import sys
import random
import results
from PIL import Image
from PySide6 import QtCore, QtWidgets, QtGui

class Main(QtWidgets.QGraphicsView):
    def __init__(self):
        super().__init__()

        self.scene = QtWidgets.QGraphicsScene()
        # self.view = QtWidgets.QGraphicsView(self.scene)
        self.setScene(self.scene)

        self.setSceneRect(0,0,1200,700)
        #Creating the legends and adding the icons

        result = results.Results()
        legend = self.sceneRect()
        text_x_pos = legend.left() + 30
        text_y_pos = legend.bottom() - 50

        icon_left = legend.left()
        icon_bottom = legend.bottom() - 30
        

        legend_icons = result.icons.image_items
        legend_texts = ["- Client", "- Domain Controller", "- Database", "- Web Server"]
        #Adding the Icons
        for icon in legend_icons:
            icon.setScale(0.25)
            icon.setPos(icon_left,icon_bottom)
            # icon.setFlags(QtWidgets.QGraphicsPixmapItem.GraphicsItemFlag.ItemIsMovable | QtWidgets.QGraphicsPixmapItem.GraphicsItemFlag.ItemIsSelectable |
            #               QtWidgets.QGraphicsPixmapItem.GraphicsItemFlag.ItemClipsToShape)
            self.scene.addItem(icon)
            icon_left+=90

        #Adding labels to the icons
        for legend_text in legend_texts:
            text = QtWidgets.QGraphicsSimpleTextItem()
            font = QtGui.QFont("Arial", 12, QtGui.QFont.Weight.Bold)
            text.setRotation(-45)
            text.setFont(font)
            text.setText(legend_text)
            text.setPos(text_x_pos - 10,text_y_pos+10)
            self.scene.addItem(text)
            text_x_pos+=98

        #Border Around the Legend
        legend_width = 400
        legend_height = 250
        legend_border = QtWidgets.QGraphicsRectItem(0,550,legend_width,legend_height)

        pen = QtGui.QPen(QtGui.QColor("black"))
        pen.setWidth(2)
        legend_border.setPen(pen)

        self.scene.addItem(legend_border)

        #Create results class and then plot results method, we'll have to pass in a Qgraphics view 
        result.plot_results(self.scene)

        self.resize(1200,875)





            
if __name__ == "__main__":
    app = QtWidgets.QApplication([])
    widget = Main()
    widget.show()

    sys.exit(app.exec())
