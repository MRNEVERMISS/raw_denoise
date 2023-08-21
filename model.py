import tensorflow as tf

####from preprocessing import lenet_preprocessing

slim = tf.contrib.slim

# def Encoder_Block(input_tensor,channel,scopes):
#     #with tf.name_scope(name):
#     num_outputs1=input_tensor.get_shape()[3].value//4
   
#     conv1 = slim.separable_conv2d(inputs=input_tensor,num_outputs=num_outputs1,kernel_size=[5,5],depth_multiplier=1)
#     ##conv2 = tf.nn.relu(conv1, name = None)
#     num_outputs11 = conv1.get_shape()[3].value
#     conv2 = slim.relu(conv1,num_outputs=num_outputs11)

#     num_outputs2=4*conv2.get_shape()[3].value
#     conv3 = slim.separable_conv2d(inputs=conv2,num_outputs=num_outputs2,kernel_size=[5,5],depth_multiplier=1)
#     print("fuck size:")
#     print(input_tensor.shape)
#     output=tf.add(input_tensor,conv3,name=scopes)
#    # output = slim.bias_add(input_tensor,conv3,scope=scopes)

    # return output




def Encoder_Block(input_tensor,channel,scopes):#,name2):
    #with tf.name_scope(name):
    num_outputs1=channel//4
   
    conv1 = slim.separable_conv2d(inputs=input_tensor,num_outputs=num_outputs1,kernel_size=[5,5],depth_multiplier=1)
    ##conv2 = tf.nn.relu(conv1, name = None)
    num_outputs11 = conv1.get_shape()[3].value
    conv2 = slim.relu(conv1,num_outputs=num_outputs11)

    num_outputs2=channel
    conv3 = slim.separable_conv2d(inputs=conv2,num_outputs=num_outputs2,kernel_size=[5,5],depth_multiplier=1)
    output=tf.add(input_tensor,conv3,name=scopes)
   # output = slim.bias_add(input_tensor,conv3,scope=scopes)
    return output



def Decoder_Block(input_tensor,channel,scopes):#,name2):
    #with tf.name_scope(name):
    #num_outputs = int(input_tensor.shape)
    num_outputs1 = channel
    conv1 = slim.separable_conv2d(inputs=input_tensor,num_outputs=num_outputs1,kernel_size=[3,3],depth_multiplier=1)
    ##conv2 = tf.nn.relu(conv1, name = None)
    num_outputs11 = conv1.get_shape()[3].value
    conv2 = slim.relu(conv1,num_outputs=num_outputs11)
    ##num_outputs2 = int(conv2.shape)
    num_outputs2 = channel
    conv3 = slim.separable_conv2d(inputs=conv2,num_outputs=num_outputs2,kernel_size=[3,3],depth_multiplier=1)
    
    print("input_tensor.shape:")
    print(input_tensor.shape)
    output=tf.add(input_tensor,conv3,name=scopes)
    return output

def Upsample_Block(x,out_shape,scopes):
    ##slim.conv2d_transpose
    ##这里的size不对
    ##slim.conv2d_transpose(x,ps_features,2,stride=1,activation_fn=activation)
    out=slim.conv2d_transpose(x,out_shape,2,stride=2,scope=scopes)
    return out
    

def Downsample_Block(input_tensor,channel,scopes):
    #with tf.name_scope(name):
    ##num_outputs = int(input_tensor.shape)//4
    num_outputs1 = channel//4
    conv1 = slim.separable_conv2d(inputs=input_tensor,num_outputs=num_outputs1,stride=2,kernel_size=[5,5],depth_multiplier=1)
    ##conv2 = tf.nn.relu(conv1, name = None)
    num_outputs11 = conv1.get_shape()[3].value
    conv2 = slim.relu(conv1,num_outputs=num_outputs11)
    # conv2 = slim.relu(conv1)
    num_outputs2 = 4*conv2.get_shape()[3].value
    conv3 = slim.separable_conv2d(inputs=conv2,num_outputs=num_outputs2,stride=1,kernel_size=[5,5],depth_multiplier=1)
    num_outputs3 = channel
    input_tensor2 = slim.separable_conv2d(inputs=input_tensor,num_outputs=num_outputs3,stride=2,kernel_size=[3,3],depth_multiplier=1)
    output=tf.add(input_tensor2,conv3,name=scopes)
    #output = slim.bias_add(input_tensor2,conv3)
    return output


def denoise_net(images):#,endpoints):
    #endpoints["input"] = images
    input_s_out = slim.conv2d(images, 16, [3,3], scope='input_stage')
    #endpoints["input_stage"] = input_s_out

    ## encoding stage 1
    ES1_mid = Downsample_Block(input_s_out,64,"downsample_block_1")
    ES1 = Encoder_Block(ES1_mid,64,"encoder_stage_1")
    #endpoints["encoder_stage_1"] = ES1

    ##  encoding stage 2
    ES2_mid = Downsample_Block(ES1,128,"downsample_block_2")
    ES2 = Encoder_Block(ES2_mid,128,"encoder_stage_2")
    #endpoints["encoder_stage_2"] = ES2

    ##  encoding stage 3
    ES3_mid = Downsample_Block(ES2,256,"downsample_block_3")
    ES3_mid = Encoder_Block(ES3_mid,256,"encoder_stage_3")
    ES3_mid = Encoder_Block(ES3_mid,256,"encoder_stage_3_1")
    ES3 = Encoder_Block(ES3_mid,256,"encoder_stage_3_2")
    #endpoints["encoder_stage_3_2"] = ES3

    ##  encoding stage 4
    ES4_mid = Downsample_Block(ES3,512,"downsample_block_4")
    ES4_mid = Encoder_Block(ES4_mid,512,"encoder_stage_4")
    ES4_mid = Encoder_Block(ES4_mid,512,"encoder_stage_4_1")
    ES4 = Encoder_Block(ES4_mid,512,"encoder_stage_4_2")
    #endpoints["encoder_stage_4"] = ES4

    # slim.separable_conv2d(input_s_out,num_outputs3,stride=2,kernel_size=3)      #input_s_out

    ## decoding stage 1
    DS1_mid = Decoder_Block(ES4,512,"decoder_block_1")
    DS1 = Upsample_Block(DS1_mid,64,"decoder_stage_1")
    #endpoints["decoder_stage_1"] = DS1

    ### element wise add
    ES3_Trans = slim.separable_conv2d(inputs=ES3,num_outputs=64,stride=1,kernel_size=[3,3],depth_multiplier=1)
    print(ES3_Trans.shape)
    print("DS1")
    print(DS1.shape)
    DS2_in = tf.add(ES3_Trans,DS1)


    ## decoding stage 2
    DS2_mid = Decoder_Block(DS2_in,64,"decoder_block_2")
    DS2 = Upsample_Block(DS2_mid,32,"decoder_stage_2")
    #endpoints["decoder_stage_2"] = DS2

    ### element wise add
    ES2_Trans = slim.separable_conv2d(inputs=ES2,num_outputs=32,stride=1,kernel_size=[3,3],depth_multiplier=1)
    #slim.separable_conv2d(ES2)
    DS3_in = tf.add(ES2_Trans,DS2)


    ## decoding stage 3
    DS3_mid = Decoder_Block(DS3_in,32,"decoder_block_3")
    DS3 = Upsample_Block(DS3_mid,32,"decoder_stage_3")
    #endpoints["decoder_stage_1"] = DS3

    ### element wise add
    ES1_Trans = slim.separable_conv2d(inputs=ES1,num_outputs=32,stride=1,kernel_size=[3,3],depth_multiplier=1)
    #slim.separable_conv2d(ES1)
    DS4_in = tf.add(ES1_Trans,DS3)

    ## decoding stage 4
    DS4_mid = Decoder_Block(DS4_in,32,"decoder_block_4")
    DS4 = Upsample_Block(DS4_mid,16,"decoder_stage_4")
    #endpoints["decoder_stage_1"] = DS4



    ### element wise add
    input_s_out_trans = slim.separable_conv2d(inputs=input_s_out,num_outputs=16,stride=1,kernel_size=[3,3],depth_multiplier=1)
    ##slim.separable_conv2d(input_s_out)
    output_stage_in = tf.add(input_s_out_trans,DS4)
    print("the shape of the tensor output_stage_in is:")
    print(output_stage_in.shape)

    output_1 = Decoder_Block(output_stage_in,16,"decoder_block_final")
    # print("the shape of the tensor output_1 is:")
    # print(output_1.shape)
    output = slim.conv2d(output_1,4,[3,3],scope="output")
    #endpoints["output"] = output

    print("the shape of tensor output is:")
    print(output.shape)


    ### element wise add
    output_final = tf.add(images,output,name="output_final")



    return output_final



# def load_batch(dataset, batch_size=32, height=512, width=512, is_training=False):
#     data_provider = slim.dataset_data_provider.DatasetDataProvider(dataset)

#     image, label = data_provider.get(['image', 'label'])

#     image = lenet_preprocessing.preprocess_image(
#         image,
#         height,
#         width,
#         is_training)

#     images, labels = tf.train.batch(
#         [image, label],
#         batch_size=batch_size,
#         allow_smaller_final_batch=True)

#     return images, labels
