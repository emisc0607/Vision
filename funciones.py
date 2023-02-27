import cv2
import numpy as np

def grises(img, h, w):
    gris = np.zeros((h, w), dtype = np.uint8)
    b = img[:, :, 0]
    g = img[:, :, 1]
    r = img[:, :, 2]
    for i in range(0, h):
        for j in range(0, w):
            gris[i, j] = 0.114*b[i, j] + 0.587*g[i, j] + 0.299*r[i, j]
    return gris

def binaria(img, h, w, n):
    gris = np.zeros((h, w), dtype = np.uint8)
    binn = np.zeros((h, w), dtype = np.uint8)
    gris = grises(img, h, w)
    for i in range(0, h):
        for j in range(0, w):
            if(gris[i, j] > n):
                binn[i, j] = 255
            else: binn[i, j] = 0
    return binn

def suma(img, h, w, n):
    gris = np.zeros((h, w), dtype = np.uint8)
    suma = np.zeros((h, w), dtype = np.float32)
    gris = grises(img, h, w)
    for i in range(0, h):
        for j in range(0, w):
            suma[i, j] = gris[i, j] + n
            if(suma[i, j] > 255):
                suma[i, j] = 255
    return suma

def resta(img, h, w, n):
    gris = np.zeros((h, w), dtype = np.uint8)
    resta = np.zeros((h, w), dtype = np.float32)
    gris = grises(img, h, w)
    for i in range(0, h):
        for j in range(0, w):
            resta[i, j] = gris[i, j] - n
            if(resta[i, j] <= 0):
                resta[i, j] = 0
    return resta

def multiplicacion(img, h, w, n):
    gris = np.zeros((h, w), dtype = np.uint8)
    multiplicacion = np.zeros((h, w), dtype = np.float32)
    gris = grises(img, h, w)
    for i in range(0, h):
        for j in range(0, w):
            multiplicacion[i, j] = gris[i, j] * n
            if(multiplicacion[i, j] > 255.0):
                multiplicacion[i, j] = 255.0
    return multiplicacion

def division(img, h, w, n):
    gris = np.zeros((h, w), dtype = np.uint8)
    division = np.zeros((h, w), dtype = np.float32)
    gris = grises(img, h, w)
    for i in range(0, h):
        for j in range(0, w):
            division[i, j] = gris[i, j] / n
            if(division[i, j] <= 0):
                division[i, j] = 0
    return division

def negativo(img, h, w):
    gris = np.zeros((h, w), dtype = np.uint8)
    neg = np.zeros((h, w), dtype = np.float32)
    gris = grises(img, h, w)
    for i in range(0, h):
        for j in range(0, w):
            neg[i, j] = 255 - gris[i, j]
    return neg

def promedio(img, h, w):
    gris = np.zeros((h, w), dtype = np.uint8)
    fprom = np.zeros((h, w), dtype = np.float32)
    gris = grises(img, h, w)
    a = 0
    aux = 0
    for i in range(1, h - 1):
        for j in range(1, w - 1):
                aux = 0
                a = 0
                for vi in range(i - 1, i + 2):
                    for vj in range(j - 1, j + 2):
                        aux = gris[vi, vj] + a
                        a = aux
                fprom[i, j] = aux / 9.0
    return fprom

#def mediana

#def moda