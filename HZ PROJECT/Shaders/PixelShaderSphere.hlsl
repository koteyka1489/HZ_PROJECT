
cbuffer CBuf
{
    float4 face_colors;
};

float4 main() : SV_Target
{
    float4 res = face_colors;
    
    return res;
}