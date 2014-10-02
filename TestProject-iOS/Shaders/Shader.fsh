//
//  Shader.fsh
//  TestProject-iOS
//
//  Created by Jon S on 02/10/14.
//  Copyright (c) 2014 Team-Innis. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
