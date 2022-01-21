struct LightColor
{
    float4      diffuse;
    float4      ambient;
    float4      specular;
};


struct LightInfo
{
    LightColor  color;
    float4	    position;
    float4	    direction;
    int		    lightType;
    float	    range;
    float	    angle;
    int  	    padding;
};

struct LightParams
{
    int         g_lightCount;
    int         g_lightPadding1;
    int         g_lightPadding2;
    int         g_lightPadding3;
    LightInfo   g_light[50];

};

struct Transform_Params
{
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProjection;
    row_major matrix g_matWV;
    row_major matrix g_matWVP;


};

struct Texture_On
{
    int     g_tex_0_on;
    int     g_tex_1_on;
    int     g_tex_2_on;
    int     g_tex_3_on;
    int     g_tex_4_on;

};


Texture2D g_tex_0;
Texture2D g_tex_1;
Texture2D g_tex_2;
Texture2D g_tex_3;
Texture2D g_tex_4;

cbuffer LightInfoMation : register ( b0 )
{
    LightParams g_lightParams;
};

SamplerState samLinear : register(s0);



cbuffer GLOBAL_PARAMS
{

   
    Transform_Params g_TransformParmas;
    Texture_On  g_Tex_On;
   
}






