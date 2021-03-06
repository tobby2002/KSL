'''
손가락 예측 모델
CNN + LSTM

# Structure of data directory
/train
        /label0
        /label1
                /sample0
                /sample1
                        /sequence1.jpg
                        /sequence2.jpg
                        ...
                        /sequence74.jpg
                        /Spoints.txt
                /sample2
                ...
                /sampleN
        /label2
        /label3
        ...
        /labelM
'''

import scripts.interfaceUtils as util
util.showProcess('Start Program')
import PYTHONPATH
import scripts.dataFormater as df
import scripts.dataPloter as dp
import scripts.models as models
import scripts.train as train
import scripts.defines as define
from scripts.Path import Path
import numpy as np
import tensorflow as tf
from keras import backend as K
util.showProcess('Loading TF Session')
sess = tf.Session()
K.set_session(sess)
from keras.preprocessing.image import ImageDataGenerator

DATASET_PATH_TRAIN = '../data/ConvLSTM/train'
DATASET_PATH_TEST = '../data/ConvLSTM/test'
IMAGE_SIZE    = (140, 140)
IMAGE_SIZE_CONCAT = (140, 280)
BATCH_SIZE    = 15
NUM_EPOCHS    = util.inputInt('How many epochs?')
isLoadWeight = util.inputInt('Load weight? (1 to yes)')
overwrite = True
sampleSize_train = len(df.getSamplePathList(DATASET_PATH_TRAIN))
sampleSize_test = len(df.getSamplePathList(DATASET_PATH_TEST))
util.showDivisionSingle()
print('train: ' + str(sampleSize_train))
print('test: ' + str(sampleSize_test))

train_imgGen = ImageDataGenerator(
    #preprocessing_function=preprocess_input,
    #rescale=1./255,
    rotation_range=3,
    shear_range=0.5,
    zoom_range=0.03,
    width_shift_range=0.03,
    height_shift_range=0.03,
    channel_shift_range=0.5,
    #vertical_flip=False,
    #horizontal_flip=False,
    fill_mode='nearest'
)

test_imgGen = ImageDataGenerator(
    #rescale = 1./255
)

train_batchIter = df.generator_multiple(
    train_imgGen,
    DATASET_PATH_TRAIN,
    IMAGE_SIZE,
    BATCH_SIZE
)

test_batchIter = df.generator_multiple(
    test_imgGen,
    DATASET_PATH_TEST,
    IMAGE_SIZE,
    BATCH_SIZE
)
'''
util.showProcess('Class indices')
for cls, idx in train_batchIter.class_indices.items():
    print('Class #{} = {}'.format(idx, cls))
'''
# write data plot graph
dp.plotSpointDataList(Path.get('train'), 2, 2, False, Path.get('img') + '\\d_graph')
dp.plotSpointDataList(Path.get('train'), 2, 2, True, Path.get('img') + '\\d_image')
print('data plot done')

'''
_, imglist, _ = df.ROI_loadData('D:/Projects/Git/KSL/data/ConvLSTM/train/2_둘/2018-05-30_005101_2_kyg', False, (80, 80, 3))
import os
j = 0

for i in train_imgGen.flow(
    imglist,
    save_to_dir='preview',
    save_format='jpeg',
    save_prefix='t',
    batch_size=70):

    j+=1
    util.input('next?')
'''

# make model, b1/b2는 구조 print용
util.showProcess('Model Generating')
model = models.Model_B2_FT(IMAGE_SIZE_CONCAT + (1,))

# plot to file
models.saveModelDescription(model, Path.get('img'), False)

# Load Weight
if isLoadWeight == 1:
    util.showProcess('Loading Weight')
    models.loadWeight(model, Path.get('weight'))
'''
# Train
util.showProcess('Train')
roiSampleList = df._ROI_loadAllSamplePaths(DATASET_PATH_TRAIN)

spointData, imageList, label = \
    df.ROI_loadDataListAll(DATASET_PATH_TRAIN, False, True, IMAGE_SIZE)

spointDatat, imageListt, labelt = \
    df.ROI_loadDataListAll(DATASET_PATH_TEST, False, False, IMAGE_SIZE)

model.fit(imageList, label,
    batch_size=BATCH_SIZE,
    epochs=NUM_EPOCHS,
    )
'''
# Train
util.showProcess('Train')
model.fit_generator(
    train_batchIter,
    steps_per_epoch=sampleSize_train/BATCH_SIZE,
    epochs=NUM_EPOCHS,
    #validation_data=test_batchIter,
    #validation_steps=sampleSize_test/BATCH_SIZE,
    max_queue_size=10,
)
'''
#Predict
util.showProcess('Predict from train data')
acc = train.calculateAccuracy(imageList, label, len(label), model, 1, BATCH_SIZE)
print('acc : ' + str(acc))

util.showProcess('Predict from test data')
acc = train.calculateAccuracy(imageListt, labelt, len(labelt), model, 1, BATCH_SIZE)
print('acc : ' + str(acc))
'''

#Predict
util.showProcess('Predict from train data')

_, imageList, labelList = \
    df.ROI_loadDataListAll(DATASET_PATH_TRAIN, False, False, IMAGE_SIZE)
acc = train.calculateAccuracy(imageList, labelList, len(labelList), model, 1, BATCH_SIZE)
print('acc : ' + str(acc))

util.showProcess('Predict from test data')
_, imageList, labelList = \
    df.ROI_loadDataListAll(DATASET_PATH_TEST, False, False, IMAGE_SIZE)
acc = train.calculateAccuracy(imageList, labelList, len(labelList), model, 1, BATCH_SIZE)
print('acc : ' + str(acc))

'''
array = model.predict_generator(
    train_batchIter,
    steps=sampleSize_train/BATCH_SIZE,
    verbose=1,
)
acc = train.calcurateAcc(array, test_batchIter)
print('acc : ' + str(acc))

#Predict
util.showProcess('Predict')
array = model.predict_generator(
    test_batchIter,
    steps=sampleSize_test/BATCH_SIZE,
    verbose=1,
)
acc = train.calcurateAcc(array, test_batchIter)
print('acc : ' + str(acc))
'''
# Write Weight
if overwrite:
    util.showProcess('Saving Weight')
    models.saveWeight(model, Path.get('weight'))

sess.close()