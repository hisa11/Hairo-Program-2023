'''
事前準備
1.Microsft Store（https://www.microsoft.com/store/productid/9NRWMJP3717K?ocid=pdpshare）もしくは公式サイト（https://www.python.org/downloads/)をインストールする
2.VSコード拡張機能で「python」と「python for VScode」をインストールする
3.winボタン右クリックで出現する「ターミナル(管理者)」に「pip install --user --upgrade pipとpython -m pip install opencv-python numpy PyQt5 pythonnetとpip install opencv-python」を書き、実行する
4.後はこのプログラムを実行する
'''
# カメラモジュールをインポート
import cv2

# ウィンドウの名前を設定
window_name = "Camera"

# カメラの番号を指定（0はデフォルトのカメラ）
camera_id = 0

# カメラを開く
camera = cv2.VideoCapture(camera_id)

# カメラが正しく開けたか確認
if not camera.isOpened():
    print("カメラが開けませんでした")
    exit()

# 無限ループ
while True:
    # 1秒待つ
    cv2.waitKey(1000)

    # カメラから画像を読み込む
    ret, frame = camera.read()

    # 画像が正しく読み込めたか確認
    if not ret:
        print("画像が読み込めませんでした")
        break

    # 画像をウィンドウに表示する
    cv2.imshow(window_name, frame)

    # キーボードのqキーが押されたらループを抜ける
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# カメラを閉じる
camera.release()

# ウィンドウを閉じる
cv2.destroyAllWindows()
