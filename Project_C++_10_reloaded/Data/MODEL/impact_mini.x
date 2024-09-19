xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 92;
 -5.00000;5.00000;-5.00000;,
 -0.31250;0.93750;-0.93750;,
 -0.23438;0.23438;-0.70313;,
 -0.93750;0.31250;-0.93750;,
 0.31250;0.93750;-0.93750;,
 0.23438;0.23438;-0.70313;,
 5.00000;5.00000;-5.00000;,
 0.93750;0.31250;-0.93750;,
 -0.23438;-0.23438;-0.70313;,
 -0.93750;-0.31250;-0.93750;,
 0.23438;-0.23438;-0.70313;,
 0.93750;-0.31250;-0.93750;,
 -0.31250;-0.93750;-0.93750;,
 -5.00000;-5.00000;-5.00000;,
 0.31250;-0.93750;-0.93750;,
 5.00000;-5.00000;-5.00000;,
 5.00000;5.00000;-5.00000;,
 0.93750;0.93750;-0.31250;,
 0.70313;0.23438;-0.23438;,
 0.93750;0.31250;-0.93750;,
 0.93750;0.93750;0.31250;,
 0.70313;0.23438;0.23438;,
 5.00000;5.00000;5.00000;,
 0.93750;0.31250;0.93750;,
 0.70313;-0.23438;-0.23438;,
 0.93750;-0.31250;-0.93750;,
 0.70313;-0.23438;0.23438;,
 0.93750;-0.31250;0.93750;,
 0.93750;-0.93750;-0.31250;,
 5.00000;-5.00000;-5.00000;,
 0.93750;-0.93750;0.31250;,
 5.00000;-5.00000;5.00000;,
 5.00000;5.00000;5.00000;,
 0.31250;0.93750;0.93750;,
 0.23438;0.23438;0.70313;,
 0.93750;0.31250;0.93750;,
 -0.31250;0.93750;0.93750;,
 -0.23438;0.23438;0.70313;,
 -5.00000;5.00000;5.00000;,
 -0.93750;0.31250;0.93750;,
 0.23438;-0.23438;0.70313;,
 0.93750;-0.31250;0.93750;,
 -0.23438;-0.23438;0.70313;,
 -0.93750;-0.31250;0.93750;,
 0.31250;-0.93750;0.93750;,
 5.00000;-5.00000;5.00000;,
 -0.31250;-0.93750;0.93750;,
 -5.00000;-5.00000;5.00000;,
 -5.00000;5.00000;5.00000;,
 -0.93750;0.93750;0.31250;,
 -0.70313;0.23438;0.23438;,
 -0.93750;0.31250;0.93750;,
 -0.93750;0.93750;-0.31250;,
 -0.70313;0.23438;-0.23438;,
 -5.00000;5.00000;-5.00000;,
 -0.93750;0.31250;-0.93750;,
 -0.70313;-0.23438;0.23438;,
 -0.93750;-0.31250;0.93750;,
 -0.70313;-0.23438;-0.23438;,
 -0.93750;-0.31250;-0.93750;,
 -0.93750;-0.93750;0.31250;,
 -5.00000;-5.00000;5.00000;,
 -0.93750;-0.93750;-0.31250;,
 -5.00000;-5.00000;-5.00000;,
 -0.31250;0.93750;0.93750;,
 -0.23438;0.70313;0.23438;,
 -0.93750;0.93750;0.31250;,
 0.31250;0.93750;0.93750;,
 0.23438;0.70313;0.23438;,
 0.93750;0.93750;0.31250;,
 -0.23438;0.70313;-0.23438;,
 -0.93750;0.93750;-0.31250;,
 0.23438;0.70313;-0.23438;,
 0.93750;0.93750;-0.31250;,
 -0.31250;0.93750;-0.93750;,
 -5.00000;5.00000;-5.00000;,
 0.31250;0.93750;-0.93750;,
 5.00000;5.00000;-5.00000;,
 -0.93750;-0.93750;0.31250;,
 -0.23438;-0.70313;0.23438;,
 -0.31250;-0.93750;0.93750;,
 0.23438;-0.70313;0.23438;,
 0.31250;-0.93750;0.93750;,
 0.93750;-0.93750;0.31250;,
 -0.93750;-0.93750;-0.31250;,
 -0.23438;-0.70313;-0.23438;,
 0.23438;-0.70313;-0.23438;,
 0.93750;-0.93750;-0.31250;,
 -5.00000;-5.00000;-5.00000;,
 -0.31250;-0.93750;-0.93750;,
 0.31250;-0.93750;-0.93750;,
 5.00000;-5.00000;-5.00000;;
 
 54;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;3,2,8,9;,
 4;2,5,10,8;,
 4;5,7,11,10;,
 4;9,8,12,13;,
 4;8,10,14,12;,
 4;10,11,15,14;,
 4;16,17,18,19;,
 4;17,20,21,18;,
 4;20,22,23,21;,
 4;19,18,24,25;,
 4;18,21,26,24;,
 4;21,23,27,26;,
 4;25,24,28,29;,
 4;24,26,30,28;,
 4;26,27,31,30;,
 4;32,33,34,35;,
 4;33,36,37,34;,
 4;36,38,39,37;,
 4;35,34,40,41;,
 4;34,37,42,40;,
 4;37,39,43,42;,
 4;41,40,44,45;,
 4;40,42,46,44;,
 4;42,43,47,46;,
 4;48,49,50,51;,
 4;49,52,53,50;,
 4;52,54,55,53;,
 4;51,50,56,57;,
 4;50,53,58,56;,
 4;53,55,59,58;,
 4;57,56,60,61;,
 4;56,58,62,60;,
 4;58,59,63,62;,
 4;48,64,65,66;,
 4;64,67,68,65;,
 4;67,22,69,68;,
 4;66,65,70,71;,
 4;65,68,72,70;,
 4;68,69,73,72;,
 4;71,70,74,75;,
 4;70,72,76,74;,
 4;72,73,77,76;,
 4;78,79,80,61;,
 4;79,81,82,80;,
 4;81,83,31,82;,
 4;84,85,79,78;,
 4;85,86,81,79;,
 4;86,87,83,81;,
 4;88,89,85,84;,
 4;89,90,86,85;,
 4;90,91,87,86;;
 
 MeshMaterialList {
  1;
  54;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;1.000000;0.000000;;
  }
 }
 MeshNormals {
  96;
  0.333484;-0.333484;-0.881803;,
  0.169213;-0.329670;-0.928808;,
  -0.169213;-0.329670;-0.928808;,
  0.329670;-0.169213;-0.928808;,
  0.167053;-0.167053;-0.971693;,
  -0.167053;-0.167053;-0.971693;,
  0.329670;0.169213;-0.928808;,
  0.167053;0.167053;-0.971693;,
  -0.167053;0.167053;-0.971693;,
  0.333484;0.333484;-0.881803;,
  0.169213;0.329670;-0.928808;,
  -0.169213;0.329670;-0.928808;,
  -0.333484;-0.333484;-0.881803;,
  0.928808;-0.329670;0.169213;,
  0.928808;-0.329670;-0.169213;,
  -0.329670;-0.169213;-0.928808;,
  0.971693;-0.167053;0.167053;,
  0.971693;-0.167053;-0.167053;,
  -0.329670;0.169213;-0.928808;,
  0.971693;0.167053;0.167053;,
  0.971693;0.167053;-0.167053;,
  -0.333484;0.333484;-0.881803;,
  0.928808;0.329670;0.169213;,
  0.928808;0.329670;-0.169213;,
  0.881803;-0.333484;-0.333484;,
  -0.169213;-0.329670;0.928808;,
  0.169213;-0.329670;0.928808;,
  0.928808;-0.169213;-0.329670;,
  -0.167053;-0.167053;0.971693;,
  0.167053;-0.167053;0.971693;,
  0.928808;0.169213;-0.329670;,
  -0.167053;0.167053;0.971693;,
  0.167053;0.167053;0.971693;,
  0.881803;0.333484;-0.333484;,
  -0.169213;0.329670;0.928808;,
  0.169213;0.329670;0.928808;,
  0.333484;-0.333484;0.881803;,
  -0.928808;-0.329670;-0.169213;,
  -0.928808;-0.329670;0.169213;,
  0.329670;-0.169213;0.928808;,
  -0.971693;-0.167053;-0.167053;,
  -0.971693;-0.167053;0.167053;,
  0.329670;0.169213;0.928808;,
  -0.971693;0.167053;-0.167053;,
  -0.971693;0.167053;0.167053;,
  0.333484;0.333484;0.881803;,
  -0.928808;0.329670;-0.169213;,
  -0.928808;0.329670;0.169213;,
  0.167053;0.971693;-0.167053;,
  -0.167053;0.971693;-0.167053;,
  0.167053;0.971693;0.167053;,
  -0.167053;0.971693;0.167053;,
  0.167053;-0.971693;-0.167053;,
  -0.167053;-0.971693;-0.167053;,
  0.167053;-0.971693;0.167053;,
  -0.167053;-0.971693;0.167053;,
  0.881803;-0.333484;0.333484;,
  0.928808;-0.169213;0.329670;,
  0.928808;0.169213;0.329670;,
  0.881803;0.333484;0.333484;,
  -0.333484;-0.333484;0.881803;,
  -0.329670;-0.169213;0.928808;,
  -0.329670;0.169213;0.928808;,
  -0.333484;0.333484;0.881803;,
  -0.881803;-0.333484;-0.333484;,
  -0.928808;-0.169213;-0.329670;,
  -0.881803;-0.333484;0.333484;,
  -0.928808;-0.169213;0.329670;,
  -0.928808;0.169213;-0.329670;,
  -0.928808;0.169213;0.329670;,
  -0.881803;0.333484;-0.333484;,
  -0.881803;0.333484;0.333484;,
  0.333484;0.881803;-0.333484;,
  0.169213;0.928808;-0.329670;,
  0.329670;0.928808;-0.169213;,
  -0.169213;0.928808;-0.329670;,
  -0.333484;0.881803;-0.333484;,
  -0.329670;0.928808;-0.169213;,
  0.329670;0.928808;0.169213;,
  -0.329670;0.928808;0.169213;,
  0.169213;0.928808;0.329670;,
  0.333484;0.881803;0.333484;,
  -0.169213;0.928808;0.329670;,
  -0.333484;0.881803;0.333484;,
  0.329670;-0.928808;-0.169213;,
  0.169213;-0.928808;-0.329670;,
  0.333484;-0.881803;-0.333484;,
  -0.169213;-0.928808;-0.329670;,
  -0.329670;-0.928808;-0.169213;,
  -0.333484;-0.881803;-0.333484;,
  0.329670;-0.928808;0.169213;,
  -0.329670;-0.928808;0.169213;,
  0.333484;-0.881803;0.333484;,
  0.169213;-0.928808;0.329670;,
  -0.169213;-0.928808;0.329670;,
  -0.333484;-0.881803;0.333484;;
  54;
  4;0,1,4,3;,
  4;1,2,5,4;,
  4;2,12,15,5;,
  4;3,4,7,6;,
  4;4,5,8,7;,
  4;5,15,18,8;,
  4;6,7,10,9;,
  4;7,8,11,10;,
  4;8,18,21,11;,
  4;56,13,16,57;,
  4;13,14,17,16;,
  4;14,24,27,17;,
  4;57,16,19,58;,
  4;16,17,20,19;,
  4;17,27,30,20;,
  4;58,19,22,59;,
  4;19,20,23,22;,
  4;20,30,33,23;,
  4;60,25,28,61;,
  4;25,26,29,28;,
  4;26,36,39,29;,
  4;61,28,31,62;,
  4;28,29,32,31;,
  4;29,39,42,32;,
  4;62,31,34,63;,
  4;31,32,35,34;,
  4;32,42,45,35;,
  4;64,37,40,65;,
  4;37,38,41,40;,
  4;38,66,67,41;,
  4;65,40,43,68;,
  4;40,41,44,43;,
  4;41,67,69,44;,
  4;68,43,46,70;,
  4;43,44,47,46;,
  4;44,69,71,47;,
  4;72,73,48,74;,
  4;73,75,49,48;,
  4;75,76,77,49;,
  4;74,48,50,78;,
  4;48,49,51,50;,
  4;49,77,79,51;,
  4;78,50,80,81;,
  4;50,51,82,80;,
  4;51,79,83,82;,
  4;84,52,85,86;,
  4;52,53,87,85;,
  4;53,88,89,87;,
  4;90,54,52,84;,
  4;54,55,53,52;,
  4;55,91,88,53;,
  4;92,93,54,90;,
  4;93,94,55,54;,
  4;94,95,91,55;;
 }
 MeshTextureCoords {
  92;
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.333330;1.000000;,
  0.666670;0.666670;,
  0.666670;1.000000;,
  1.000000;0.666670;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;;
 }
}
