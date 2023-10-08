# このプログラムの事前準備はカメラプログラムの初代を見てください
import cv2
 
# カメラのデバイスIDを設定 本番直前にしたの数値をいじってください。
camera1 = cv2.VideoCapture(1)  # 0は通常のカメラ
camera2 = cv2.VideoCapture(2)  # 1は2番目のカメラ...

if not camera1.isOpened() or not camera2.isOpened():
    print("カメラが見つかりません")
    exit()

while True:
    # 1秒ごとに画像をキャプチャ
    ret1, frame1 = camera1.read()
    ret2, frame2 = camera2.read()

    if not ret1 or not ret2:
        print("画像をキャプチャできません")
        break

    # 画像を表示
    cv2.imshow("Camera 1", frame1)
    cv2.imshow("Camera 2", frame2)

    # ここの「16」の数字をいじるとfpsが変わります。※33にすると約30fps 16にすると約60fps
    if cv2.waitKey(16) & 0xFF == ord('q'):
        break

# カメラを解放してウィンドウを閉じる
camera1.release()
camera2.release()
cv2.destroyAllWindows()
