import tkinter as tk
from tkinter import *
from tkinter import filedialog
from PIL import Image
from PIL import ImageTk

import cv2
import numpy as np
import funciones as fn

#pillow, tk, m
def abrir_img():
    ruta_img = filedialog.askopenfilename(filetype = [("image", ".jpg"), ("image", ".png")])
    global img
    if (len(ruta_img) > 0):
        print(str(ruta_img))
        img = cv2.imread(ruta_img)
        h, c, w= img.shape
        print(str(h) + ' ' + str(w) + ' ' + str(c))
        img2 = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        img2 = cv2.resize(img2, (320, 240))
        im = Image.fromarray(img2)
        img1 = ImageTk.PhotoImage(image = im)
        img_in.configure(image=img1)
        img_in.image = img1

####    Opcion con OpenCV

        #img = cv2.imread(ruta_img)
        #h, c, w= img.shape
        #print(str(h) + ' ' + str(w) + ' ' + str(c))
        #cv2.imshow("Original", img)
        #cv2.waitKey(0)
        #cv2.destroyAllWindows()

####    End
    else:
        print("No hay imagen para mostrar")

def gris():
    global img
    h, w, c = img.shape
    out = fn.grises(img, h, w)
    show_out(out)  

def show_out(imgg):

    img2 = cv2.cvtColor(imgg, cv2.COLOR_BGR2RGB)
    img2 = cv2.resize(img2, (320, 240))
    im = Image.fromarray(img2)
    img1 = ImageTk.PhotoImage(image = im)
    img_out.configure(image = img1)
    img_out.image = img1

def binaria():
    global img
    h, w, c = img.shape
    n = int(val.get())
    out = fn.binaria(img, h, w, n)
    show_out(out) 

def negativa():
    global img
    h, w, c = img.shape
    out = fn.negativo(img, h, w)
    show_out(out.astype(np.uint8)) 

def addition():
    global img
    h, w, c = img.shape
    n = int(val.get())
    out = fn.suma(img, h, w, n)
    show_out(out.astype(np.uint8)) 

def sustraction():
    global img
    h, w, c = img.shape
    n = int(val.get())
    out = fn.resta(img, h, w, n)
    show_out(out.astype(np.uint8)) 

def multiplica():
    global img
    h, w, c = img.shape
    n = int(val.get())
    out = fn.multiplicacion(img, h, w, n)
    show_out(out.astype(np.uint8)) 

def divide():
    global img
    h, w, c = img.shape
    n = int(val.get())
    out = fn.division(img, h, w, n)
    show_out(out.astype(np.uint8)) 

def filtro_promedio():
    global img
    h, w, c = img.shape
    out = fn.promedio(img, h, w)
    show_out(out.astype(np.uint8)) 


vn = tk.Tk()
vn.title("Vision - Maestria")
vn.geometry("1000x600")
barra_menus = tk.Menu()
menu_archivo = tk.Menu(barra_menus, tearoff = False)
menu_funciones = tk.Menu(barra_menus, tearoff = False)
menu_filtros = tk.Menu(barra_menus, tearoff = False)

barra_menus.add_cascade( menu = menu_archivo, label = "Archivo")
menu_archivo.add_command(label = "Abrir imagen", command = abrir_img)

barra_menus.add_cascade( menu = menu_funciones, label = "Funciones")
menu_funciones.add_command(label = "Grises", command = gris)
menu_funciones.add_command(label = "Binaria", command = binaria)
menu_funciones.add_command(label = "Negativa", command = negativa)
menu_funciones.add_command(label = "Suma", command = addition)
menu_funciones.add_command(label = "Resta", command = sustraction)
menu_funciones.add_command(label = "Multiplicacion", command = multiplica)
menu_funciones.add_command(label = "Division", command = divide)

barra_menus.add_cascade( menu = menu_filtros, label = "Funciones")
menu_filtros.add_command(label = "Promedio", command = filtro_promedio)

vn.config(menu = barra_menus)
img_in = Label(vn)
img_in.place(x = 10, y = 10)
img_out = Label(vn)
img_out.place(x = 510, y = 10)

val = tk.Entry(vn, width = 10)
Label(vn, text= "Nivel de umbral =").place(x= 10, y= 330)
val.place(x = 10, y = 350)


vn.mainloop()
