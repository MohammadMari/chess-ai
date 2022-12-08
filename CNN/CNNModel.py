import tensorflow.keras.models as models
import tensorflow.keras.layers as layers
import tensorflow.keras.optimizers as optimizers
from tensorflow.keras.callbacks import ModelCheckpoint
import numpy as np

def build_model(conv_size, conv_depth):
  board3d = layers.Input(shape=(14, 8, 8))

  # adding the convolutional layers
  x = board3d
  for _ in range(conv_depth):
    x = layers.Conv2D(filters=conv_size, kernel_size=3, padding='same', activation='relu')(x)
  x = layers.Flatten()(x)
  x = layers.Dense(64, 'relu')(x)
  x = layers.Dense(1, 'sigmoid')(x)

  return models.Model(inputs=board3d, outputs=x)

def get_dataset(fn):
	container = np.load(fn, allow_pickle=True)
	b, s = container['b'], container['s']
	s = np.asarray(s / abs(s).max() / 2 + 0.5, dtype=np.float32) # normalization (0 - 1)
	return b, s

def get_model_summary():
  model = build_model(32, 4)
  return model.summary()

def main():
   print('Building Model')
   model = build_model(32, 4)
   print('Model Built')
   
   print('Getting Dataset')
   x_train, y_train = get_dataset('./Datasets/Black/DatasetBlack02.npz')
   x_train.transpose()
   print('x_train: ', x_train.shape)
   print('y_train: ', y_train.shape)
   
   model.compile(optimizer=optimizers.Adam(5e-4), loss='mean_squared_error')
   model.summary()
   
   print('Fitting to model')
   model.fit(x_train, y_train,
          batch_size=2048,
          epochs=1000,
          verbose=1,
          validation_split=0.1)
   
   model.save('blackModel02.h5')
   print('Model Saved as blackModel01.h5')

if __name__ == "__main__":
   main()