#!/usr/bin/python
import rospy

params = rospy.get_param('/hand')

for f in params:
  for m in params[f]:
    print f+'_'+m,'::',params[f][m]['id']
    rospy.set_param('/namesToIds/'+f+'_'+m,params[f][m]['id'])
