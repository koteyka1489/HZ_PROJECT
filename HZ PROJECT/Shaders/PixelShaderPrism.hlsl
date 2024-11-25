cbuffer CBuf
{
    float4 face_colors[7];
};

float4 main(uint tid : SV_PrimitiveID) : SV_Target
{
    float4 res = face_colors[tid / 2];
    
    return res;
}