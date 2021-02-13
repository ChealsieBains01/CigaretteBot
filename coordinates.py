import numpy as np
import skimage
from mrcnn import visualize

calibrate = [256, 256]

def process_image(image_path, model):
    img = skimage.io.imread(image_path)
    img_arr = np.array(img)
    results = model.detect([img_arr], verbose=1)
    r = results[0]
    coordinates = []
    for cig in r['rois']:
        x = calibrate[0] - (cig[1] + cig[3])/2
        y = calibrate[0] - (cig[0] + cig[2])/2
        coordinates.append([x, y])
    #     For Testing:
    # visualize.display_instances(img, r['rois'], r['masks'], r['class_ids'], "cigs",
    #                             r['scores'], figsize=(5, 5))
    return coordinates

