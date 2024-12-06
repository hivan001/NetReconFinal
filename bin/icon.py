import sys
import random
import os
import copy
from PIL import Image
from PySide6 import QtCore, QtWidgets, QtGui

class Icon(QtWidgets.QGraphicsView):
    image_items = []
    services = {
        "20":"FTP-DATA",
        "21":"FTP",
        "22":"SSH",
        "23":"TELNET",
        "25":"SMTP",
        "53":"DNS",
        "69":"TFTP",
        "80":"HTTP",
        "88":"KERBEROS",
        "110":"POP3",
        "143":"IMAP",
        "443":"HTTPS",
        "445":"SMB",
        "464":"KERBEROS-PASS",
        "587":"SMTP",
        "636":"LDAP-SSL",
        "3306":"MYSQL",
        "5432":"POSTGRESQL",
        "3389":"RDP",
        "27017":"MONGODB",
        "1521":"ORACLEDB",
        "1433":"MSSQL",
        "8080":"HTTP-PROXY"
    }
    def __init__(self):
        super().__init__()

        pc_path = "static/pc.png"
        ad_path = "static/ad.png"
        db_path = "static/db.png"
        web_path = "static/web.png"

        #resizing images for standardization
        image_paths = [pc_path, ad_path, db_path, web_path]

        for image_path in image_paths:
            image = Image.open(image_path)
            width = 300
            height = 400
            resize = image.resize((width,height))
            resize.save(image_path)


        pc_pixmap = QtGui.QPixmap(pc_path)
        ad_pixmap = QtGui.QPixmap(ad_path)
        db_pixmap = QtGui.QPixmap(db_path)
        web_pixmap = QtGui.QPixmap(web_path)

        pc_image_item = QtWidgets.QGraphicsPixmapItem(pc_pixmap)
        ad_image_item = QtWidgets.QGraphicsPixmapItem(ad_pixmap)
        db_image_item = QtWidgets.QGraphicsPixmapItem(db_pixmap)
        web_image_item = QtWidgets.QGraphicsPixmapItem(web_pixmap)

        self.image_items.append(pc_image_item)
        self.image_items.append(ad_image_item)
        self.image_items.append(db_image_item)
        self.image_items.append(web_image_item)
        
    def get_service(self, port):
        if port in self.services:
            return f" - {self.services[port]}"
        else:
            return ""
       
    def make_icon_group(self, data, icon):
        icon_x_pos = icon.pos().x()
        icon_y_pos = icon.pos().y()
        icon_width = icon.pixmap().width()

        # Create a QWidget with a layout for the toggle button
        main_widget = QtWidgets.QWidget()
        main_layout = QtWidgets.QVBoxLayout(main_widget)

        main_widget.toggle_button = QtWidgets.QPushButton("IP: " + data["IP"])
        main_widget_font = QtGui.QFont("Arial", 50)
        main_widget.toggle_button.setFont(main_widget_font)
        main_widget.toggle_button.setCheckable(True)
        main_widget.toggle_button.setEnabled(True)
        main_widget.toggle_button.setChecked(False)
        main_widget.toggle_button.setStyleSheet(
            """QPushButton {
            border: 3px solid black;
            border-radius: 10px;
            padding: 5px;
            }
            """
        )
        main_widget.toggle_button.setFixedSize(800, 100)
        main_layout.addWidget(main_widget.toggle_button)

        # Proxy widget for the toggle button
        toggle_button = QtWidgets.QGraphicsProxyWidget()
        toggle_button.setWidget(main_widget)
        toggle_button.setPos(icon_x_pos + icon_width, icon_y_pos)


        # Create content area as a separate QWidget
        content_widget = QtWidgets.QWidget()
        content_layout = QtWidgets.QVBoxLayout(content_widget)
        content_widget.label = QtWidgets.QLabel("TCP Ports: ")

        # Looping through the ports and adding to the icon
        for port in data["TCP Ports"]:
            current_text = content_widget.label.text()
            content_widget.label.setText(current_text + "\n" + port + self.get_service(port))


        content_font = QtGui.QFont("Arial", 40)
        content_widget.label.setFont(content_font)
        content_widget.label.setAlignment(QtCore.Qt.AlignTop | QtCore.Qt.AlignLeft)
        content_widget.setFixedSize(800, 800)
        content_widget.setStyleSheet(
                        """QWidget {
            border: 3px solid black;
            border-radius: 10px;
            padding: 5px;
            }
            """
        )
        content_layout.addWidget(content_widget.label)

        # Proxy widget for the content area
        content_x_pos = toggle_button.pos().x()
        content_y_pos = toggle_button.pos().y() + 150
        content = QtWidgets.QGraphicsProxyWidget()
        content.setWidget(content_widget)
        content.setPos(content_x_pos, content_y_pos)  # Adjusted position

        # Group all items
        group = QtWidgets.QGraphicsItemGroup()
        group.addToGroup(icon)
        group.addToGroup(toggle_button)
        group.addToGroup(content)

        return group

    def make_pc_icon(self, data):
        pixmap = self.image_items[0].pixmap()
        pc = QtWidgets.QGraphicsPixmapItem(pixmap)
        return self.make_icon_group(data,pc)
    
    def make_ad_icon(self, data):
        pixmap = self.image_items[1].pixmap()
        ad = QtWidgets.QGraphicsPixmapItem(pixmap)
        return self.make_icon_group(data,ad)
    
    def make_db_icon(self, data):
        pixmap = self.image_items[2].pixmap()
        db = QtWidgets.QGraphicsPixmapItem(pixmap)
        return self.make_icon_group(data,db)
    
    def make_web_icon(self, data):
        pixmap = self.image_items[3].pixmap()
        web = QtWidgets.QGraphicsPixmapItem(pixmap)
        return self.make_icon_group(data,web)




        

    