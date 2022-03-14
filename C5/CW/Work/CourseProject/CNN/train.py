import tensorflow as tf
from tensorflow import keras
from keras import layers
import numpy as np
import cv2

train_materials_path = "D:/Storage/Andrew/BMSTU/BMSTU/CW/Work/CourseProject/TrainMaterials/"

import os, os.path

x_train = []
y_train = []

#size of dataset
dataset_size = len(os.listdir(train_materials_path))
classes = 8
image_size = (256, 256)
image_shape = (256, 256, 1)
batch_size = 128

import os

clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8,8))
count = 0

for name in os.listdir(train_materials_path):
  fpath_img = train_materials_path + name
  image = cv2.imread(fpath_img, cv2.IMREAD_GRAYSCALE)
  
  min_dim = min(image.shape)
  w = min_dim
  h = min_dim
  center = image.shape
  x = center[1]/2 - w/2
  y = center[0]/2 - h/2

  crop_img = image[int(y):int(y+h), int(x):int(x+w)]

  img_clh = clahe.apply(crop_img)
  new_img = cv2.resize(img_clh, image_size)

  x_train.append(new_img)

  index = int(name.split('_')[1])
  res_vec = [0] * classes
  res_vec[index] = 1
  
  y_train.append(res_vec)
  count += 1
  if count % 100 == 0:
    os.system('cls')
    print(count, ':', dataset_size)

x_train = np.array(x_train)
y_train = np.array(y_train)    

from keras.layers.pooling import MaxPooling2D
from keras import Sequential
from keras.layers import Conv2D, Flatten, Dense, MaxPool2D, AveragePooling2D, BatchNormalization

model = Sequential()

model.add(Conv2D(16, kernel_size=(9,9), strides=(1,1), padding='same', input_shape=image_shape))
model.add(Conv2D(16, kernel_size=(9,9), strides=(1,1), padding='same'))
model.add(Conv2D(16, kernel_size=(9,9), strides=(1,1), padding='same'))
model.add(Conv2D(16, kernel_size=(9,9), strides=(1,1), padding='same'))
model.add(MaxPooling2D(pool_size=(2,2)))

model.add(Conv2D(32, kernel_size=(7,7), strides=(1,1), padding='same'))
model.add(Conv2D(32, kernel_size=(7,7), strides=(1,1), padding='same'))
model.add(Conv2D(32, kernel_size=(7,7), strides=(1,1), padding='same'))
model.add(Conv2D(32, kernel_size=(7,7), strides=(1,1), padding='same'))
model.add(MaxPooling2D(pool_size=(2,2)))

model.add(Conv2D(64, kernel_size=(5,5), strides=(1,1), padding='same'))
model.add(Conv2D(64, kernel_size=(5,5), strides=(1,1), padding='same'))
model.add(Conv2D(64, kernel_size=(5,5), strides=(1,1), padding='same'))
model.add(Conv2D(64, kernel_size=(5,5), strides=(1,1), padding='same'))
model.add(MaxPooling2D(pool_size=(2,2)))

model.add(Conv2D(128, kernel_size=(3,3), strides=(1,1), padding='same'))
model.add(Conv2D(128, kernel_size=(3,3), strides=(1,1), padding='same'))
model.add(Conv2D(128, kernel_size=(3,3), strides=(1,1), padding='same'))
model.add(Conv2D(128, kernel_size=(3,3), strides=(1,1), padding='same'))
model.add(MaxPooling2D(pool_size=(2,2)))

model.add(Conv2D(128, kernel_size=(3,3), strides=(1,1), padding='same'))
model.add(Conv2D(128, kernel_size=(3,3), strides=(1,1), padding='same'))
model.add(Conv2D(128, kernel_size=(3,3), strides=(1,1), padding='same'))
model.add(Conv2D(128, kernel_size=(3,3), strides=(1,1), padding='same'))
model.add(MaxPooling2D(pool_size=(2,2)))

# flatten output of conv
model.add(Flatten())

# hidden layer
model.add(Dense(256, activation='relu'))
model.add(Dense(128, activation='relu'))
model.add(Dense(64, activation='relu'))
model.add(Dense(32, activation='relu'))
#model.add(Dropout(0.3))

# output layer
model.add(Dense(classes, activation='softmax'))

from keras import losses
from keras import metrics

epochs = 20

opt = tf.keras.optimizers.Adam(learning_rate=0.001, decay=1e-3 / 200)

callbacks = [
    keras.callbacks.ModelCheckpoint("save_model_at_{epoch}.h5"),
]


model.compile(loss=losses.categorical_crossentropy, optimizer=opt, metrics=metrics.Accuracy())

history = model.fit(
    x_train, y_train, epochs=epochs, callbacks=callbacks, validation_split=0.2,
)

import matplotlib.pyplot as plt
   
plt.figure(1)  
  
# summarize history for accuracy  
  
plt.subplot(211)  
plt.plot(history.history['accuracy'])  
plt.plot(history.history['val_accuracy'])  
plt.title('model accuracy')  
plt.ylabel('accuracy')  
plt.xlabel('epoch')  
plt.legend(['train', 'test'], loc='upper left')  
  
# summarize history for loss  
  
plt.subplot(212)  
plt.plot(history.history['loss'])  
plt.plot(history.history['val_loss'])  
plt.title('model loss')  
plt.ylabel('loss')  
plt.xlabel('epoch')  
plt.legend(['train', 'test'], loc='upper left')  
plt.show()  

img_array = tf.expand_dims(x_train[index], 0)  # Create batch axis

index = 11000
cv2.imshow(x_train[index])

predictions = model.predict(img_array)
print(predictions, y_train[index])

model.save('new_model.h5')