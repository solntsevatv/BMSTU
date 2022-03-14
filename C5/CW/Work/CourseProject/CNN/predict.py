def predict_model(fpath_img: str) -> int:
    import cv2
    import numpy as np
    import keras
    import tensorflow as tf
    from keras import layers
    
    try:
        image_size = (256, 256)

        clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8,8))
        image = cv2.imread(fpath_img, cv2.IMREAD_GRAYSCALE)
        
        max_index = 0
        count = 0
        max_val = 0

        min_dim = min(image.shape)
        w = min_dim
        h = min_dim
        center = image.shape
        x = center[1]/2 - w/2
        y = center[0]/2 - h/2

        crop_img = image[int(y):int(y+h), int(x):int(x+w)]

        img_clh = clahe.apply(crop_img)
        new_img = cv2.resize(img_clh, image_size)

        from keras.models import load_model
        import os
        dir_path = os.path.dirname(os.path.realpath(__file__))
        model = load_model(dir_path + "\model.h5")
        
        img_array = tf.expand_dims(new_img, 0)
        predictions = model.predict(img_array)
        
        for pred in predictions[0]:
            if max_val < pred:
                max_val = pred
                max_index = count
            count += 1
            
        return max_index
    except:
        return -1

if __name__ == '__main__':
    fpath_img = 'test.png'
    print(predict_model(fpath_img))