import numpy as np
import cv2 as cv
import sys 
import argparse
import os

import PIL
from PIL import Image

from skimage.feature import match_descriptors
import imageio.v2 as imageio
import torch

import scipy
import scipy.io
import scipy.misc

import cv2 as cv

from lib.model_test import D2Net
from lib.utils import preprocess_image
from lib.pyramid import process_multiscale

def extract_features(image, features):

    #IBG.Default arguments as it must work easily for users...
    model_file = os.path.dirname(os.path.abspath(__file__)) + '/models/d2_tf.pth'
    max_edge = 1600
    max_sum_edges = 2800
    preprocessing = 'caffe'
    multiscale = False
    use_cuda = torch.cuda.is_available()
    device = torch.device("cuda:0" if use_cuda else "cpu")
    output_type = 'npz'
    output_extension = '.d2-net'
    path = os.path.abspath(image)
    
    # Creating CNN model
	
    model = D2Net(
        model_file=model_file,
        use_relu=True,
        use_cuda=torch.cuda.is_available()
    )
	
    # Process the file
    
    image = imageio.imread(image)
    if len(image.shape) == 2:
        image = image[:, :, np.newaxis]
        image = np.repeat(image, 3, -1)
		
    resized_image = image

    input_image = preprocess_image(
        resized_image,
        preprocessing=preprocessing
    )	
    #input_image = image	
	
    with torch.no_grad():
        if multiscale:
            keypoints, scores, descriptors = process_multiscale(
                torch.tensor(
                    input_image[np.newaxis, :, :, :].astype(np.float32),
                    device=device
                ),
                model
            )
        else:
            keypoints, scores, descriptors = process_multiscale(
                torch.tensor(
                    input_image[np.newaxis, :, :, :].astype(np.float32),
                    device=device
                ),
                model,
                scales=[1]
            )


    keypoints = keypoints[:, [1, 0, 2]]

    s = cv.FileStorage(features, cv.FileStorage_WRITE)
    s.write('keypoints', keypoints)
    s.write('scores', scores)
    s.write('descriptors', descriptors)
    s.release()

if __name__ == "__main__":
    
    parser = argparse.ArgumentParser("Extract keypoints for a given image")
    parser.add_argument("--image", type=str, required=True, help='image path')
    parser.add_argument("--features", type=str, required=True, help='Output features file')
    args = parser.parse_args()
    extract_features(args.image, args.features)
