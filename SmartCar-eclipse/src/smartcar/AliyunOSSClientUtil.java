package smartcar;

import java.io.ByteArrayInputStream;  
import java.io.File;  
import java.io.FileInputStream;  
import java.io.InputStream;  
  
import org.apache.log4j.Logger;  
  
import com.aliyun.oss.OSSClient;  
import com.aliyun.oss.model.Bucket;  
import com.aliyun.oss.model.OSSObject;  
import com.aliyun.oss.model.ObjectMetadata;  
import com.aliyun.oss.model.PutObjectResult;  
  
/** 
 * @class:AliyunOSSClientUtil 
 * @descript:javaʹ�ð�����OSS�洢�����ϴ�ͼƬ 
 * @date:2017��3��16�� ����5:58:08 
 * @author sang 
 */  
public class AliyunOSSClientUtil {  
    //log��־  
    private static Logger logger = Logger.getLogger(AliyunOSSClientUtil.class);  
    //������API���ڻ���������  
    private static String ENDPOINT;  
    //������API����ԿAccess Key ID  
    private static String ACCESS_KEY_ID;  
    //������API����ԿAccess Key Secret  
    private static String ACCESS_KEY_SECRET;  
    //������API��bucket����  
    private static String BACKET_NAME;  
    //������API���ļ�������  
    private static String FOLDER;  
    //��ʼ������  
    static{  
        ENDPOINT = OSSClientConstants.ENDPOINT;  
        ACCESS_KEY_ID = OSSClientConstants.ACCESS_KEY_ID;  
        ACCESS_KEY_SECRET = OSSClientConstants.ACCESS_KEY_SECRET;  
        BACKET_NAME = OSSClientConstants.BACKET_NAME;  
        FOLDER = OSSClientConstants.FOLDER;  
    }  
      
    /** 
     * ��ȡ������OSS�ͻ��˶��� 
     * @return ossClient 
     */  
    public static  OSSClient getOSSClient(){  
        return new OSSClient(ENDPOINT,ACCESS_KEY_ID, ACCESS_KEY_SECRET);  
    }  
  
    /** 
     * �����洢�ռ� 
     * @param ossClient      OSS���� 
     * @param bucketName �洢�ռ� 
     * @return 
     */  
    public  static String createBucketName(OSSClient ossClient,String bucketName){  
        //�洢�ռ�  
        final String bucketNames=bucketName;  
        if(!ossClient.doesBucketExist(bucketName)){  
            //�����洢�ռ�  
            Bucket bucket=ossClient.createBucket(bucketName);  
            logger.info("�����洢�ռ�ɹ�");  
            return bucket.getName();  
        }  
        return bucketNames;  
    }  
      
    /** 
     * ɾ���洢�ռ�buckName 
     * @param ossClient  oss���� 
     * @param bucketName  �洢�ռ� 
     */  
    public static  void deleteBucket(OSSClient ossClient, String bucketName){    
        ossClient.deleteBucket(bucketName);     
        logger.info("ɾ��" + bucketName + "Bucket�ɹ�");    
    }    
      
    /** 
     * ����ģ���ļ��� 
     * @param ossClient oss���� 
     * @param bucketName �洢�ռ� 
     * @param folder   ģ���ļ�������"qj_nanjing/" 
     * @return  �ļ����� 
     */  
    public  static String createFolder(OSSClient ossClient,String bucketName,String folder){  
        //�ļ�����   
        final String keySuffixWithSlash =folder;  
        //�ж��ļ����Ƿ���ڣ��������򴴽�  
        if(!ossClient.doesObjectExist(bucketName, keySuffixWithSlash)){  
            //�����ļ���  
            ossClient.putObject(bucketName, keySuffixWithSlash, new ByteArrayInputStream(new byte[0]));  
            logger.info("�����ļ��гɹ�");  
            //�õ��ļ�����  
            OSSObject object = ossClient.getObject(bucketName, keySuffixWithSlash);  
            String fileDir=object.getKey();  
            return fileDir;  
        }  
        return keySuffixWithSlash;  
    }  
      
     /**   
        * ����keyɾ��OSS�������ϵ��ļ�   
        * @param ossClient  oss���� 
        * @param bucketName  �洢�ռ�  
        * @param folder  ģ���ļ����� ��"qj_nanjing/" 
        * @param key Bucket�µ��ļ���·����+�ļ��� �磺"upload/cake.jpg" 
        */      
       public static void deleteFile(OSSClient ossClient, String bucketName, String folder, String key){      
            ossClient.deleteObject(bucketName, folder + key);     
            logger.info("ɾ��" + bucketName + "�µ��ļ�" + folder + key + "�ɹ�");    
       }   
      
    /** 
     * �ϴ�ͼƬ��OSS 
     * @param ossClient  oss���� 
     * @param file �ϴ��ļ����ļ�ȫ·���磺D:\\image\\cake.jpg�� 
     * @param bucketName  �洢�ռ� 
     * @param folder ģ���ļ����� ��"qj_nanjing/" 
     * @return String ���ص�ΨһMD5����ǩ�� 
     * */  
    public static  String uploadObject2OSS(OSSClient ossClient, File file, String bucketName, String folder) {  
        String resultStr = null;  
        try {  
            //������������ʽ�ϴ��ļ�  
            InputStream is = new FileInputStream(file);  
            //�ļ���  
            String fileName = file.getName();   
            //�ļ���С  
            Long fileSize = file.length();   
            //�����ϴ�Object��Metadata    
            ObjectMetadata metadata = new ObjectMetadata();  
            //�ϴ����ļ��ĳ���  
            metadata.setContentLength(is.available());    
            //ָ����Object������ʱ����ҳ�Ļ�����Ϊ  
            metadata.setCacheControl("no-cache");   
            //ָ����Object������Header  
            metadata.setHeader("Pragma", "no-cache");    
            //ָ����Object������ʱ�����ݱ����ʽ  
            metadata.setContentEncoding("utf-8");    
            //�ļ���MIME�������ļ������ͼ���ҳ���룬�������������ʲô��ʽ��ʲô�����ȡ�ļ�������û�û��ָ�������Key���ļ�������չ�����ɣ�  
            //���û����չ������Ĭ��ֵapplication/octet-stream  
            metadata.setContentType(getContentType(fileName));    
            //ָ����Object������ʱ�����ƣ�ָʾMINME�û����������ʾ���ӵ��ļ����򿪻����أ����ļ����ƣ�  
            metadata.setContentDisposition("filename/filesize=" + fileName + "/" + fileSize + "Byte.");    
            //�ϴ��ļ�   (�ϴ��ļ�������ʽ)  
            PutObjectResult putResult = ossClient.putObject(bucketName, folder + fileName, is, metadata);    
            //�������  
            resultStr = putResult.getETag();  
        } catch (Exception e) {  
            e.printStackTrace();  
             logger.error("�ϴ�������OSS�������쳣." + e.getMessage(), e);    
        }  
        return resultStr;  
    }  
  
    /** 
     * ͨ���ļ����жϲ���ȡOSS�����ļ��ϴ�ʱ�ļ���contentType 
     * @param fileName �ļ��� 
     * @return �ļ���contentType 
     */  
    public static  String getContentType(String fileName){  
        //�ļ��ĺ�׺��  
        String fileExtension = fileName.substring(fileName.lastIndexOf("."));  
        if(".bmp".equalsIgnoreCase(fileExtension)) {  
            return "image/bmp";  
        }  
        if(".gif".equalsIgnoreCase(fileExtension)) {  
            return "image/gif";  
        }  
        if(".jpeg".equalsIgnoreCase(fileExtension) || ".jpg".equalsIgnoreCase(fileExtension)  || ".png".equalsIgnoreCase(fileExtension) ) {  
            return "image/jpeg";  
        }  
        if(".html".equalsIgnoreCase(fileExtension)) {  
            return "text/html";  
        }  
        if(".txt".equalsIgnoreCase(fileExtension)) {  
            return "text/plain";  
        }  
        if(".vsd".equalsIgnoreCase(fileExtension)) {  
            return "application/vnd.visio";  
        }  
        if(".ppt".equalsIgnoreCase(fileExtension) || "pptx".equalsIgnoreCase(fileExtension)) {  
            return "application/vnd.ms-powerpoint";  
        }  
        if(".doc".equalsIgnoreCase(fileExtension) || "docx".equalsIgnoreCase(fileExtension)) {  
            return "application/msword";  
        }  
        if(".xml".equalsIgnoreCase(fileExtension)) {  
            return "text/xml";  
        }  
        //Ĭ�Ϸ�������  
        return "image/jpeg";  
    }  
      
    //����  
    public static String init(String path,String name) throws Exception
    {  
        //��ʼ��OSSClient  
        OSSClient ossClient=AliyunOSSClientUtil.getOSSClient();  
        //�ϴ��ļ�  
        String files=path+",";  
        String[] file=files.split(",");  
        for(String filename:file){  
            //System.out.println("filename:"+filename);  
            File filess=new File(filename);  
            String md5key = AliyunOSSClientUtil.uploadObject2OSS(ossClient, filess, BACKET_NAME, FOLDER);    
            logger.info("�ϴ�����ļ�MD5����Ψһǩ��:" + md5key);    
            //�ϴ�����ļ�MD5����Ψһǩ��:40F4131427068E08451D37F02021473A  
        }
        //System.out.println(3+":"+path+":"+name);
        String url="https://hust-cqq.oss-cn-shenzhen.aliyuncs.com/SmartCar/camera/"+name;
        String s = new AESDecode().imgIdResult(ACCESS_KEY_ID,ACCESS_KEY_SECRET,url);
        //System.out.println(4+":"+s);
         return s;
    }  
      
      
}
