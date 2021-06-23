// /*
//  *   Copyright (c) 2021 Kirk Nickish
//  *   All rights reserved.
//  */

// #include "MatrixMath.h"
// #include <memory>

// class MatrixMath
// {
//     public:
//     std::shared_ptr<float[]> vals;
//     int total_size;
//     const int original_size;

//     MatrixMath(std::shared_ptr<float[]> floats, int len)
//     :vals(floats)
//     ,total_size(len)
//     ,original_size(len)
//     {
//     }

//     // std::string toString() 
//     // {
//     //     std::ostringstream strout;
//     //     strout<<"Matrix (size "<<total_size<<"):\n";
//     //     int square = sqrt(total_size);
//     //     for (int i = 0; i<square;i++)
//     //     {
//     //         for (int j = 0; j<square;j++)
//     //         {";
//     //         }
//     //         strout<<"\n";
//     //     }
//     //     strout<<"\n";
//     //     return strout.str();
//     // }

//     static std::shared_ptr<float[]> mat_mul(const std::shared_ptr<float[]>& vals_l, const std::shared_ptr<float[]>& vals_r, int len)
//     {
        
//         std::shared_ptr<float[]> ret {new float[len]};
//         uint16_t square = (int) sqrt((float)len);
//         std::unique_ptr<float[]> a_list {new float[square]};
//         std::unique_ptr<float[]> b_list {new float[square]};
//         for(int i = 0;i<square;i++)
//         {
//             for (int j = 0; j<square; j++)
//             {
//                 for(int k = 0;k<square;k++)
//                 {
//                     a_list[k] = (*vals_l)[i*square+k];
//                     b_list[k] = (*vals_r)[k*square+j];
//                 }
//                 for(int k = 0;k<square;k++)
//                 {
//                     a_list[k] = a_list[k]*b_list[k];
//                 }
//                 float acc = 0;
//                 for(int k = 0;k<square;k++)
//                 {
//                     acc+=a_list[k];
//                 }
//                 (*ret)[i*square+j] = acc;
//             }
//         }
//         return ret;
//     }

//     static std::shared_ptr<float[]> mat_add(const std::shared_ptr<float[]>& vals_l, const std::shared_ptr<float[]>& vals_r, int len)
//     {
        
//         std::shared_ptr<float[]> ret {new float[len]};
//         uint16_t square = (int) sqrt((float)len);
//         for(int i = 0;i<square;i++)
//         {
//             for (int j = 0; j<square; j++)
//             {
//                 (*ret)[i*square+j] = (*vals_l)[i*square+j] + (*vals_r)[i*square+j];
//             }
//         }
//         return ret;
//     }

//     static std::shared_ptr<float[]> mat_sub(const std::shared_ptr<float[]>& vals_l, const std::shared_ptr<float[]>& vals_r, int len)
//     {
        
//         std::shared_ptr<float[]> ret {new float[len]};
//         uint16_t square = (int) sqrt((float)len);
//         for(int i = 0;i<square;i++)
//         {
//             for (int j = 0; j<square; j++)
//             {
//                 (*ret)[i*square+j] = (*vals_l)[i*square+j] - (*vals_r)[i*square+j];
//             }
//         }
//         return ret;
//     }

//     static std::shared_ptr<float[]> sign_swap(const std::shared_ptr<float[]>&vals, int len)
//     {
//         std::shared_ptr<float[]> ret {new float[len]};
//         for (int i = 0; i<len;i++)
//         {
//             (*ret)[i] = -(*vals)[i];
//         }
//         return ret;
//     }
    
//     std::shared_ptr<float[]> invert_two()
//     {
//         if (total_size!=4)
//         {
//             return vals;
//         }
//         std::shared_ptr<float[]> ret {new float[4]};

//         float a, b, c, d;
//         a = (*vals)[0];
//         b = (*vals)[1];
//         c = (*vals)[2];
//         d = (*vals)[3];
//         float det = (a*d)-(b*c);
//         if (det)
//         {
//             (*ret)[0] = d/det;
//             (*ret)[1] = -b/det;
//             (*ret)[2] = -c/det;
//             (*ret)[3] = a/det;
//             this->vals = ret;
//             return ret;
//         }
//         else
//         {
//             return vals;
//         }
//     }

//     bool fill_identity()
//     {
        
//         uint16_t base = 2;
//         uint8_t power = 1;
//         while (base<original_size)
//         {
//             power+=1;
//             base*=2;
//         }
//         uint16_t new_square_size = (int) sqrt((float)base);
//         uint16_t old_square_size = (int) sqrt((float)original_size);
        
        
//         if (new_square_size==old_square_size)
//             return original_size;
//         uint16_t size_diff = new_square_size-old_square_size;
//         std::shared_ptr<float[]> old_vals = vals;
//         std::shared_ptr<float[]> tmp {new float[base]};
//         vals = tmp;
//         if (!(vals))
//             return 0;

//         for (uint16_t i = 0; i< new_square_size; i++)
//         {
//             for (uint16_t j = 0 ; j<new_square_size ; j++)
//             {
//                 if (i>=size_diff && j>=size_diff)
//                 {
//                     (*vals)[i*new_square_size+j] = (*old_vals)[(i-(size_diff))*old_square_size + j-(size_diff)];
//                 }
//                 else
//                 {
//                     if (i==j)
//                     {
//                         (*vals)[i*new_square_size + j] = 1;
//                     }
//                     else
//                     {
//                         (*vals)[i*new_square_size + j] = 0;
//                     }
//                 }
//             }
//         }
//         this->vals = vals;
//         this->total_size = base;
//         return true;
//     }

//     int trim_identity(int size)
//     {
        
//         uint16_t base = 2;
//         uint8_t power = 1;
//         while (base<size)
//         {
//             power+=1;
//             base*=2;
//         }
//         uint16_t new_square_size = (int) sqrt((float)size);
//         uint16_t old_square_size = (int) sqrt((float)base);
        
        
//         if (new_square_size==old_square_size)
//             return size;
//         uint16_t size_diff = old_square_size-new_square_size;
//         std::shared_ptr<float[]>  old_vals = vals;
//         std::shared_ptr<float[]> vals {new float[size]};
//         if (!(vals))
//             return 0;

//         for (uint16_t i = 0; i< new_square_size; i++)
//         {
//             for (uint16_t j = 0 ; j<new_square_size ; j++)
//             {
//                 (*vals)[i*new_square_size+j] = (*old_vals)[(i+size_diff)*old_square_size + j+(size_diff)];
//             }
//         }
//         this->vals = vals;
//         this->total_size = size;
//         return base;
//     }

//     static std::shared_ptr<float[]> quarters_merge(
//         const std::shared_ptr<float[]>& e,
//         const std::shared_ptr<float[]>& f,
//         const std::shared_ptr<float[]>& g,
//         const std::shared_ptr<float[]>& h,
//         int quarter_array_size)
//     {
//         uint16_t square = (int) sqrt((float)quarter_array_size);
//         uint16_t rowsize = (int) sqrt((float)(4*quarter_array_size));
//         uint16_t half_offset = rowsize*rowsize/2;
//         std::shared_ptr<float[]> ret {new float[4*quarter_array_size]};
//         for (int i = 0;i<square;i++)
//         {
//             for (int j = 0; j<square; j++)
//             {
//                 (*ret)[i*rowsize+j] = (*e)[i*square+j];
//             }
//             for (int j = 0; j<square; j++)
//             {
//                 (*ret)[i*rowsize+j+square] = (*f)[i*square+j];
//             }
//         }
//         for (int i = 0;i<square;i++)
//         {
//             for (int j = 0; j<square; j++)
//             {
//                 (*ret)[half_offset + i*rowsize + j]            = (*g)[i*square+j];
//             }
//             for (int j = 0; j<square; j++)
//             {
//                 (*ret)[half_offset + i*rowsize + square + j]   = (*h)[i*square+j];
//             }
//         }
//         return ret;
//     }

//     std::shared_ptr<float[]> invert()
//     {

        
//         if (this->total_size==4)
//         {
//             invert_two();
//             return this->vals;
//         }
//         fill_identity();
//         int half_square = (int)((sqrt((float)total_size))/2);
//         int quarter_count = total_size/4;
//         //fill and invert e
//         std::shared_ptr<float[]> e{ new float[quarter_count]{0}};
//         for (int i = 0; i<half_square;i++)
//         {
//             for (int j = 0; j<half_square;j++)
//             {
//                 (*e)[i*half_square+j] = (*vals)[i*(half_square*2)+j];
//             }
//         }
//         std::shared_ptr<float[]> e_inv;
//         MatrixMath e_obj(e, quarter_count);
//         e_inv = e_obj.invert();


//         //fill the other submatrices
//         std::shared_ptr<float[]> f{ new float[quarter_count]{0}};
//         std::shared_ptr<float[]> g{ new float[quarter_count]{0}};
//         std::shared_ptr<float[]> h{ new float[quarter_count]{0}};
//         for (int i = 0; i<2*half_square;i++)
//         {
//             for (int j = 0; j<2*half_square;j++)
//             {
//                 if (i>=half_square || j>=half_square){
//                     if (i<half_square)
//                         {
//                             (*f)[i*half_square+(j-half_square)] = (*vals)[i*(half_square*2)+j];
//                         }
//                     else
//                     {
//                         if(j<half_square)
//                             (*g)[(i-half_square)*half_square+j] = (*vals)[i*(half_square*2)+j];
//                         else
//                             (*h)[(i-half_square)*half_square+j-half_square] = (*vals)[i*(half_square*2)+j];
//                     }
                        
//                 }
//             }
//         }

//         //inv hgef
//         MatrixMath hgef_obj = MatrixMath(mat_sub(h, mat_mul(mat_mul(g, e_inv, quarter_count),f,quarter_count), quarter_count), quarter_count);
//         std::shared_ptr<float[]> inv_hgef = hgef_obj.invert();
        
//         std::shared_ptr<float[]> e_inv_f = mat_mul(e_inv, f, quarter_count);
//         std::shared_ptr<float[]> g_e_inv = mat_mul(g, e_inv,  quarter_count);
//         MatrixMath e_inv_f_obj = MatrixMath(e_inv_f, quarter_count);
//         MatrixMath g_e_inv_obj = MatrixMath(g_e_inv, quarter_count);

//         vals = quarters_merge(
//             mat_add(
//                 e_inv, 
//                 mat_mul(
//                     mat_mul(
//                         e_inv_f, 
//                         inv_hgef, 
//                         quarter_count)
//                     ,g_e_inv, 
//                     quarter_count)
//                 ,quarter_count),
//             sign_swap(
//                 mat_mul(
//                     e_inv_f, 
//                     inv_hgef,
//                     quarter_count)
//                 ,quarter_count),
//             sign_swap(
//                 mat_mul(
//                     inv_hgef, 
//                     g_e_inv,
//                     quarter_count)
//                 ,quarter_count), 
//             inv_hgef,
//             quarter_count);

//         trim_identity(this->original_size);
//         return vals;
//     }
// };