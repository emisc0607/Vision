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

def histograma(img, h, w):
    gris  = np.zeros((h,w), dtype=np.uint8)
    gris = grises(img, h, w)
    hist = np.zeros(256)
    for i in range(0, h):
        for j in range(0, w):
            a = gris[i,j]
            hist[a] += 1;
    return hist

def ecualizacion(img, h, w):
    gris = np.zeros((h,w), dtype=np.uint8)
    gris = grises(img, h, w)
    hist = histograma(img, h, w)
    sk = np.zeros(256)
    vk = np.zeros(256)
    sk[0] = hist[0]

    for i in range(1, 256):
        sk[i] = hist[i] + sk[i-1]
    skmax = sk[255]
    ban = 0
    skmin = 0
    
    for i in range(0, 256):
        if(ban == 0):
            if(sk[i] != 0):
                skmin = sk[i]
                ban = 1

    for i in range(0, 256):
        vk[i] = round(255*(sk[i]-skmin)/(skmax-skmin))

    for i in range(0, h):
        for j in range(0, w):
            a = gris[i,j]
            gris[i, j] = vk[a]

    return gris

def histograma_color(img, h, w):
    sk = np.zeros(256)
    vk = np.zeros(256)
    hist= np.zeros(256)
    for i in range(0, h):
        for j in range(0, w):
            a = img[i,j]
            hist[a] += 1;
    
    sk[0] = hist[0]
    for i in range(1, 256):
        sk[i] = hist[i] + sk[i-1]

    skmax = sk[255]
    ban = 0
    skmin = 0 
    for i in range(0, 256):
        if(ban == 0):
            if(sk[i] != 0):
                skmin = sk[i]
                ban = 1

    for i in range(0, 256):
        vk[i] = round(255*(sk[i]-skmin)/(skmax-skmin))

    for i in range(0, h):
        for j in range(0, w):
            a = img[i,j]
            img[i, j] = vk[a] 

    return img

def ecualizar_color(img):
    h, w, c = img.shape
    b = img[:, :, 0]
    g = img[:, :, 1]
    r = img[:, :, 2]
    color = np.zeros((h,w,3), dtype=np.uint8)
    hist_c = histograma_color(b, h, w)
    color[:, :, 0] = hist_c[:, :]
    hist_c = histograma_color(g, h, w)
    color[:, :, 1] = hist_c[:, :]
    hist_c = histograma_color(r, h, w)
    color[:, :, 2] = hist_c[:, :]
    return color

def camara_web():
    video = cv2.VideoCapture(0)
    ban, frame = video.read()
    if(ban != 0):
        print("Camara detectada")
    else: 
        print("No se puede acceder a la camara")
    while(video.isOpened()):
        ban, frame = video.read()
        cv2.imshow("Imagen de la camara", frame)
        if(cv2.waitKey(1) & 0xFF == ord('c')):
            break
    video.release()
    cv2.destroyAllWindows()
    return frame

def conteo(img, h, w):
    counter = 0
    lst = []
    for i in range(0, h):
        for j in range(0, w):
            if(img[i, j] != 0):
                img[i,j] = 0
                counter += 1
                lst.append([i,j])
                while(len(lst) > 0):
                    a = lst.pop(0)
                    for ii in range(a[0] - 1, a[0] + 2):
                        for jj in range(a[1] - 1, a[1] + 2):
                            if(img[ii, jj] != 0):
                                lst.append([ii,jj])
                                img[ii, jj] = 0
    return counter