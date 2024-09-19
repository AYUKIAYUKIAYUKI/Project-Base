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
 66;
 -0.00009;5.40104;1.81188;,
 -1.99773;1.99719;0.00018;,
 0.00018;2.03368;1.96124;,
 -1.81220;5.40117;-0.00009;,
 -0.00041;2.03360;-1.96146;,
 -0.00054;5.40108;-1.81242;,
 1.99719;1.99764;-0.00031;,
 1.81183;5.40104;-0.00036;,
 -0.00031;8.25611;1.38640;,
 -1.38731;8.25579;-0.00041;,
 -0.00063;8.25602;-1.38740;,
 1.38640;8.25579;-0.00031;,
 -0.00041;10.16375;0.74997;,
 -0.75082;10.16348;-0.00049;,
 -0.00058;10.16379;-0.75110;,
 0.75033;10.16370;-0.00067;,
 -0.00036;11.16828;-0.00049;,
 5.40112;0.00054;1.81170;,
 2.03337;0.00041;1.96119;,
 5.40104;1.81220;-0.00036;,
 2.03319;-0.00004;-1.96155;,
 5.40099;0.00009;-1.81220;,
 1.99764;-1.99746;0.00004;,
 5.40121;-1.81197;-0.00027;,
 8.25602;0.00027;1.38636;,
 8.25592;1.38717;-0.00054;,
 8.25602;0.00022;-1.38735;,
 8.25615;-1.38668;-0.00041;,
 10.16388;0.00041;0.74997;,
 10.16375;0.75069;-0.00054;,
 10.16370;0.00041;-0.75114;,
 10.16388;-0.74992;-0.00063;,
 11.16859;0.00036;-0.00081;,
 -5.40081;0.00004;1.81233;,
 -1.99764;-1.99733;0.00009;,
 -2.03328;0.00009;1.96159;,
 -5.40117;-1.81215;0.00041;,
 -2.03391;0.00004;-1.96115;,
 -5.40131;-0.00022;-1.81179;,
 -5.40135;1.81201;0.00031;,
 -8.25583;-0.00009;1.38744;,
 -8.25602;-1.38712;0.00054;,
 -8.25615;-0.00054;-1.38618;,
 -8.25624;1.38677;0.00041;,
 -10.16352;-0.00031;0.75128;,
 -10.16388;-0.75100;0.00072;,
 -10.16370;-0.00031;-0.74984;,
 -10.16370;0.75033;0.00058;,
 -11.16859;-0.00014;0.00041;,
 0.00009;-5.40081;1.81220;,
 0.00027;-2.03328;1.96137;,
 1.81238;-5.40112;0.00022;,
 0.00000;-2.03328;-1.96128;,
 -0.00009;-5.40104;-1.81183;,
 -1.81197;-5.40099;0.00036;,
 0.00049;-8.25597;1.38744;,
 1.38717;-8.25543;0.00027;,
 0.00027;-8.25597;-1.38681;,
 -1.38654;-8.25574;0.00036;,
 0.00045;-10.16343;0.75100;,
 0.75087;-10.16356;0.00022;,
 0.00031;-10.16343;-0.75010;,
 -0.75028;-10.16379;0.00041;,
 0.00022;-11.16828;0.00054;,
 -0.00027;-0.00009;-2.06289;,
 0.00009;0.00018;2.06289;;
 
 128;
 3;0,1,2;,
 3;3,1,0;,
 3;3,4,1;,
 3;5,4,3;,
 3;5,6,4;,
 3;7,6,5;,
 3;0,2,7;,
 3;7,2,6;,
 3;8,3,0;,
 3;9,3,8;,
 3;9,5,3;,
 3;10,7,5;,
 3;10,5,9;,
 3;11,7,10;,
 3;8,0,11;,
 3;11,0,7;,
 3;12,9,8;,
 3;13,9,12;,
 3;13,10,9;,
 3;14,10,13;,
 3;14,11,10;,
 3;15,11,14;,
 3;12,8,15;,
 3;15,8,11;,
 3;16,12,15;,
 3;16,13,12;,
 3;16,15,14;,
 3;16,14,13;,
 3;17,6,18;,
 3;19,6,17;,
 3;19,20,6;,
 3;21,20,19;,
 3;21,22,20;,
 3;23,22,21;,
 3;17,18,23;,
 3;23,18,22;,
 3;24,19,17;,
 3;25,19,24;,
 3;25,21,19;,
 3;26,23,21;,
 3;26,21,25;,
 3;27,23,26;,
 3;24,17,27;,
 3;27,17,23;,
 3;28,25,24;,
 3;29,25,28;,
 3;29,26,25;,
 3;30,26,29;,
 3;30,27,26;,
 3;31,27,30;,
 3;28,24,31;,
 3;31,24,27;,
 3;32,28,31;,
 3;32,29,28;,
 3;32,31,30;,
 3;32,30,29;,
 3;33,34,35;,
 3;36,34,33;,
 3;36,37,34;,
 3;38,1,37;,
 3;38,37,36;,
 3;39,1,38;,
 3;33,35,39;,
 3;39,35,1;,
 3;40,36,33;,
 3;41,36,40;,
 3;41,38,36;,
 3;42,38,41;,
 3;42,39,38;,
 3;43,39,42;,
 3;40,33,43;,
 3;43,33,39;,
 3;44,41,40;,
 3;45,41,44;,
 3;45,42,41;,
 3;46,43,42;,
 3;46,42,45;,
 3;47,43,46;,
 3;47,40,43;,
 3;44,40,47;,
 3;48,44,47;,
 3;48,45,44;,
 3;48,47,46;,
 3;48,46,45;,
 3;49,22,50;,
 3;51,22,49;,
 3;51,52,22;,
 3;53,52,51;,
 3;53,34,52;,
 3;54,34,53;,
 3;49,50,54;,
 3;54,50,34;,
 3;55,51,49;,
 3;56,51,55;,
 3;56,53,51;,
 3;57,54,53;,
 3;57,53,56;,
 3;58,54,57;,
 3;55,49,58;,
 3;58,49,54;,
 3;59,56,55;,
 3;60,56,59;,
 3;60,57,56;,
 3;61,58,57;,
 3;61,57,60;,
 3;62,58,61;,
 3;59,55,62;,
 3;62,55,58;,
 3;63,59,62;,
 3;63,60,59;,
 3;63,62,61;,
 3;63,61,60;,
 3;64,20,22;,
 3;64,52,34;,
 3;20,64,6;,
 3;4,64,1;,
 3;37,64,34;,
 3;64,37,1;,
 3;52,64,22;,
 3;64,4,6;,
 3;65,18,6;,
 3;18,65,22;,
 3;65,2,1;,
 3;50,65,34;,
 3;65,35,34;,
 3;65,50,22;,
 3;35,65,1;,
 3;2,65,6;;
 
 MeshMaterialList {
  1;
  128;
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
   0.423529;0.423529;0.423529;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.423529;0.423529;0.423529;;
   TextureFilename {
    "Data\\TEXTURE\\kyrie_512.jpg";
   }
  }
 }
 MeshNormals {
  141;
  -0.703783;0.058327;0.708017;,
  -0.700411;0.033618;0.712947;,
  -0.491567;0.339640;0.801877;,
  -0.704651;0.082726;0.704715;,
  -0.702687;0.034957;-0.710640;,
  -0.704943;0.080219;-0.704713;,
  0.491592;0.339543;-0.801903;,
  0.704652;0.082708;-0.704716;,
  -0.699436;0.146617;0.699495;,
  -0.694456;0.188331;0.694451;,
  0.699466;0.146611;-0.699466;,
  0.694422;0.188198;-0.694521;,
  -0.672092;0.310996;0.671992;,
  -0.662151;0.351195;0.661981;,
  -0.662311;0.351157;-0.661840;,
  0.661910;0.351063;-0.662291;,
  0.625207;0.467085;0.625259;,
  0.058348;0.703921;0.707877;,
  0.033591;0.700610;0.712753;,
  0.082731;0.704737;0.704629;,
  0.034991;0.702531;-0.710792;,
  0.080241;0.704781;-0.704873;,
  0.339551;-0.491666;-0.801854;,
  0.082656;-0.704669;-0.704705;,
  0.146620;0.699496;0.699434;,
  0.188300;0.694504;0.694412;,
  0.146593;-0.699459;-0.699477;,
  0.188323;-0.694474;-0.694435;,
  0.310993;0.672134;0.671952;,
  0.351220;0.662191;0.661927;,
  0.350967;0.662256;-0.661997;,
  0.351084;-0.662132;-0.662058;,
  0.467094;-0.625342;0.625117;,
  -0.058230;-0.703820;0.707987;,
  -0.033531;-0.700573;0.712793;,
  -0.339481;-0.491671;0.801880;,
  -0.082596;-0.704637;0.704744;,
  -0.035058;-0.702605;-0.710716;,
  -0.058386;0.703844;-0.707951;,
  -0.082751;0.704602;-0.704761;,
  -0.146507;-0.699427;0.699527;,
  -0.188161;-0.694409;0.694544;,
  -0.188333;-0.694453;-0.694454;,
  -0.188322;0.694297;-0.694613;,
  -0.310937;-0.671945;0.672166;,
  -0.351171;-0.661931;0.662214;,
  -0.310908;0.671935;-0.672190;,
  -0.351070;0.662002;-0.662196;,
  -0.467032;0.625221;0.625283;,
  0.703809;-0.058220;0.707999;,
  0.700552;-0.033569;0.712812;,
  0.704694;-0.082613;0.704686;,
  0.702534;-0.035026;-0.710788;,
  0.704790;-0.080294;-0.704857;,
  -0.704755;-0.082768;-0.704606;,
  0.699552;-0.146558;0.699391;,
  0.694609;-0.188310;0.694304;,
  -0.699548;-0.146688;-0.699368;,
  -0.694492;-0.188335;-0.694414;,
  0.672193;-0.310957;0.671910;,
  0.662211;-0.351130;0.661954;,
  -0.671999;-0.310996;-0.672086;,
  -0.661962;-0.351135;-0.662201;,
  -0.625107;-0.466965;0.625448;,
  -0.403583;-0.403595;-0.821116;,
  -0.403456;0.403575;0.821188;,
  -0.703992;0.058027;-0.707834;,
  -0.339644;0.491665;-0.801815;,
  0.703787;0.058289;-0.708016;,
  0.700479;0.033590;-0.712882;,
  0.704863;0.080397;0.704772;,
  0.702686;0.035054;0.710636;,
  0.703954;0.058153;0.707861;,
  0.339648;0.491730;0.801773;,
  -0.699575;0.146558;-0.699368;,
  -0.694597;0.188259;-0.694330;,
  0.694449;0.188362;0.694449;,
  0.699493;0.146669;0.699426;,
  -0.672234;0.310985;-0.671856;,
  0.671952;0.310887;-0.672183;,
  0.662031;0.351202;0.662096;,
  0.672028;0.311003;0.672053;,
  -0.625348;0.467057;0.625139;,
  0.625027;0.467175;-0.625371;,
  -0.625462;0.467142;-0.624961;,
  0.058068;0.703821;-0.708000;,
  0.058286;-0.703843;-0.707960;,
  0.033588;-0.700588;-0.712776;,
  0.080345;-0.704733;0.704909;,
  0.035124;-0.702476;0.710840;,
  0.058170;-0.703764;0.708048;,
  0.491682;-0.339488;0.801871;,
  0.146546;0.699435;-0.699510;,
  0.188210;0.694497;-0.694443;,
  0.188353;-0.694457;0.694445;,
  0.146679;-0.699388;0.699530;,
  0.310847;0.672154;-0.671999;,
  0.310926;-0.672083;-0.672034;,
  0.351170;-0.662191;0.661953;,
  0.311041;-0.672093;0.671971;,
  0.467129;0.625353;0.625080;,
  0.466864;-0.625334;-0.625296;,
  0.466855;0.625436;-0.625201;,
  -0.058101;-0.703912;-0.707907;,
  -0.491675;-0.339627;-0.801817;,
  -0.033641;0.700593;-0.712768;,
  -0.080308;-0.704873;-0.704773;,
  -0.080295;0.704833;0.704815;,
  -0.034987;0.702637;0.710688;,
  -0.058080;0.703899;0.707921;,
  -0.146607;-0.699514;-0.699419;,
  -0.146669;0.699327;-0.699593;,
  -0.188281;0.694472;0.694448;,
  -0.146586;0.699479;0.699458;,
  -0.310978;-0.671996;-0.672097;,
  -0.351180;-0.661970;-0.662169;,
  -0.310959;0.672043;0.672059;,
  -0.351141;0.662064;0.662096;,
  -0.467277;-0.624995;0.625327;,
  -0.466832;0.625236;-0.625419;,
  -0.467008;-0.625151;-0.625372;,
  0.703806;-0.058135;-0.708010;,
  -0.703876;-0.058362;-0.707921;,
  -0.700511;-0.033666;-0.712848;,
  -0.704799;-0.080306;0.704847;,
  -0.702511;-0.035024;0.710811;,
  -0.703814;-0.058102;0.708005;,
  0.699496;-0.146550;-0.699448;,
  0.694468;-0.188288;-0.694451;,
  -0.694437;-0.188288;0.694482;,
  -0.699470;-0.146592;0.699466;,
  0.671969;-0.311051;-0.672090;,
  0.661900;-0.351305;-0.662173;,
  -0.661935;-0.351139;0.662226;,
  -0.671970;-0.310932;0.672144;,
  0.625364;-0.467025;0.625145;,
  -0.625079;-0.467106;-0.625370;,
  0.625053;-0.467191;-0.625333;,
  0.262340;0.538137;-0.800991;,
  0.700472;-0.035529;-0.712795;,
  0.403638;-0.403482;0.821145;;
  128;
  3;0,2,1;,
  3;3,2,0;,
  3;66,4,67;,
  3;5,4,66;,
  3;68,6,69;,
  3;7,6,68;,
  3;70,71,72;,
  3;72,71,73;,
  3;8,3,0;,
  3;9,3,8;,
  3;74,5,66;,
  3;10,7,68;,
  3;75,5,74;,
  3;11,7,10;,
  3;76,70,77;,
  3;77,70,72;,
  3;12,9,8;,
  3;13,9,12;,
  3;78,75,74;,
  3;14,75,78;,
  3;79,11,10;,
  3;15,11,79;,
  3;80,76,81;,
  3;81,76,77;,
  3;16,80,81;,
  3;82,13,12;,
  3;83,15,79;,
  3;84,14,78;,
  3;17,73,18;,
  3;19,73,17;,
  3;85,20,6;,
  3;21,20,85;,
  3;86,22,87;,
  3;23,22,86;,
  3;88,89,90;,
  3;90,89,91;,
  3;24,19,17;,
  3;25,19,24;,
  3;92,21,85;,
  3;26,23,86;,
  3;93,21,92;,
  3;27,23,26;,
  3;94,88,95;,
  3;95,88,90;,
  3;28,25,24;,
  3;29,25,28;,
  3;96,93,92;,
  3;30,93,96;,
  3;97,27,26;,
  3;31,27,97;,
  3;98,94,99;,
  3;99,94,95;,
  3;32,98,99;,
  3;100,29,28;,
  3;101,31,97;,
  3;102,30,96;,
  3;33,35,34;,
  3;36,35,33;,
  3;103,37,104;,
  3;38,67,105;,
  3;106,37,103;,
  3;39,67,38;,
  3;107,108,109;,
  3;109,108,2;,
  3;40,36,33;,
  3;41,36,40;,
  3;110,106,103;,
  3;42,106,110;,
  3;111,39,38;,
  3;43,39,111;,
  3;112,107,113;,
  3;113,107,109;,
  3;44,41,40;,
  3;45,41,44;,
  3;114,42,110;,
  3;46,43,111;,
  3;115,42,114;,
  3;47,43,46;,
  3;116,112,113;,
  3;117,112,116;,
  3;48,117,116;,
  3;118,45,44;,
  3;119,47,46;,
  3;120,115,114;,
  3;49,91,50;,
  3;51,91,49;,
  3;121,52,22;,
  3;53,52,121;,
  3;122,104,123;,
  3;54,104,122;,
  3;124,125,126;,
  3;126,125,35;,
  3;55,51,49;,
  3;56,51,55;,
  3;127,53,121;,
  3;57,54,122;,
  3;128,53,127;,
  3;58,54,57;,
  3;129,124,130;,
  3;130,124,126;,
  3;59,56,55;,
  3;60,56,59;,
  3;131,128,127;,
  3;61,58,57;,
  3;132,128,131;,
  3;62,58,61;,
  3;133,129,134;,
  3;134,129,130;,
  3;63,133,134;,
  3;135,60,59;,
  3;136,62,61;,
  3;137,132,131;,
  3;64,87,22;,
  3;64,123,104;,
  3;20,138,6;,
  3;4,64,67;,
  3;37,64,104;,
  3;138,105,67;,
  3;52,139,22;,
  3;138,69,6;,
  3;65,18,73;,
  3;89,140,91;,
  3;65,1,2;,
  3;125,65,35;,
  3;140,34,35;,
  3;140,50,91;,
  3;108,65,2;,
  3;71,140,73;;
 }
 MeshTextureCoords {
  66;
  0.691161;0.743316;,
  0.646406;0.800047;,
  0.692999;0.799439;,
  0.648491;0.743314;,
  0.644791;0.799440;,
  0.646621;0.743315;,
  0.691382;0.800039;,
  0.689294;0.743316;,
  0.685930;0.695732;,
  0.653272;0.695737;,
  0.651842;0.695733;,
  0.684504;0.695737;,
  0.678109;0.663938;,
  0.660437;0.663942;,
  0.659662;0.663937;,
  0.677338;0.663938;,
  0.668887;0.647195;,
  0.751975;0.833324;,
  0.715892;0.833327;,
  0.729708;0.803130;,
  0.667688;0.833334;,
  0.707444;0.833332;,
  0.691391;0.866624;,
  0.729711;0.863533;,
  0.778895;0.833329;,
  0.761851;0.810214;,
  0.744811;0.833330;,
  0.761855;0.856445;,
  0.792557;0.833327;,
  0.783333;0.820822;,
  0.774109;0.833327;,
  0.783333;0.845832;,
  0.794644;0.833327;,
  0.630355;0.833333;,
  0.646406;0.866622;,
  0.670107;0.833332;,
  0.608086;0.863536;,
  0.621898;0.833333;,
  0.585817;0.833337;,
  0.608083;0.803133;,
  0.592987;0.833335;,
  0.575943;0.856452;,
  0.558901;0.833342;,
  0.575939;0.810220;,
  0.563690;0.833338;,
  0.554463;0.845850;,
  0.545242;0.833338;,
  0.554463;0.820828;,
  0.543146;0.833336;,
  0.691167;0.923347;,
  0.693002;0.867221;,
  0.689307;0.923352;,
  0.644797;0.867221;,
  0.646633;0.923351;,
  0.648499;0.923350;,
  0.685952;0.970933;,
  0.684520;0.970924;,
  0.651860;0.970933;,
  0.653290;0.970929;,
  0.678131;1.002724;,
  0.677355;1.002726;,
  0.659684;1.002724;,
  0.660455;1.002730;,
  0.668907;1.019471;,
  0.643546;0.833335;,
  0.694247;0.833330;;
 }
}
