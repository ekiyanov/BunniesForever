#ifdef GL_ES                                
precision lowp float;                       
#endif                                      
                                            
varying vec4 v_fragmentColor;               
varying vec2 v_texCoord;                    
uniform sampler2D u_texture;                
                                            
void main()                                 
{                                           
    vec4 tex = texture2D(u_texture, v_texCoord);
    gl_FragColor = vec4(v_fragmentColor.rgb*v_fragmentColor.a + tex.rgb,tex.a);
}