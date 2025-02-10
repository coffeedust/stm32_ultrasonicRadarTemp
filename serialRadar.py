import tkinter as tk
import math
import serial
import time

WIDTH = 640
HEIGHT = 480
angle = 0
direction = 0
sendingAngle = 0
# 물체를 저장할 리스트 생성 [[0,10],[10,20],[각도,거리]...]
objects = [[x,0] for x in range(0, 190, 10)]
# 예시
objects[4][1] = 200
objects[10][1] = 150

ser = serial.Serial("COM3", 115200)
window = tk.Tk()
window.title("초음파 레이더")
window.geometry("640x480+3000+100")
canvas = tk.Canvas(window, width=WIDTH, height=HEIGHT, bg="black")
canvas.pack()

def drawObject(angle, distance):
    radius = WIDTH / 2
    x = radius + math.cos(angle * math.pi / 180) * distance
    y = radius - math.sin(angle * math.pi / 180) * distance
    canvas.create_oval(x-5, y-5, x+5, y+5, fill='green')

def update_scan():
    global angle
    global direction
    global objects
    global sendingAngle
    receiveDistance = 0
    # 각도 전송
    if angle % 10 == 0:
        sendingAngle = angle
        ser.write(f"A{angle:03d}\n".encode())
    # 거리 수신
    if ser.in_waiting > 0:
        data = ser.readline().decode()
        if data[0] == 'D':
            # 두번째 문자부터 숫자로 파싱
            receiveDistance = int(data[1:])
            # 해당 각도의 거리를 업데이트
            for obj in objects:
                if(obj[0] == sendingAngle):
                    obj[1] = receiveDistance
    # 레이더 선 그리기
    canvas.delete("all")
    radius = WIDTH / 2
    x = radius + math.cos(angle * math.pi / 180) * radius
    y = radius - (math.sin(angle * math.pi / 180) * radius)
    canvas.create_line(x, y, radius, radius, fill='green', width=3)
    # 감지 물체 그리기
    for obj in objects:
        if obj[1] != 0:
            drawObject(obj[0], obj[1])
    # 각도 업데이트
    if direction == 0:
        angle += 1
        if angle == 181:
            direction = 1
    else:
        angle -= 1
        if angle == -1:
            direction = 0
    # 재귀 호출
    canvas.after(50, update_scan)

update_scan()
window.mainloop()
