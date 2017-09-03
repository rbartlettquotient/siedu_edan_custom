<?php
/**********************
 ** CSS Alter
 ***********************/

function si_baseline_css_alter(&$css) {
//  unset($css[drupal_get_path('module', 'system') . '/system.menus.css']);
//  unset($css[drupal_get_path('module', 'system') . '/system.theme.css']);
//  unset($css[drupal_get_path('module', 'system') . '/system.base.css']);
//  unset($css[drupal_get_path('module', 'date_popup') . '/themes/datepicker.1.7.css']);
  if (isset($css['misc/ui/jquery.ui.core.css'])) {
    unset($css['misc/ui/jquery.ui.core.css']);
  }
  if (isset($css['misc/ui/jquery.ui.theme.css'])) {
    unset($css['misc/ui/jquery.ui.theme.css']);
  }
  if (isset($css['misc/ui/jquery.ui.datepicker.css'])) {
    unset($css['misc/ui/jquery.ui.datepicker.css']);
  }
  if (isset($css['sites/all/modules/jquery_update/replace/ui/themes/base/minified/jquery.ui.datepicker.min.css'])) {
    unset($css['sites/all/modules/jquery_update/replace/ui/themes/base/minified/jquery.ui.datepicker.min.css']);
  }
  if (isset($css['sites/all/modules/date/date_popup/themes/datepicker.1.7.css'])) {
    unset($css['sites/all/modules/date/date_popup/themes/datepicker.1.7.css']);
  }
  if (isset($css['sites/all/modules/jquery_update/replace/ui/themes/base/minified/jquery.ui.theme.min.css'])) {
    unset($css['sites/all/modules/jquery_update/replace/ui/themes/base/minified/jquery.ui.theme.min.css']);
  }
  if (isset($css['sites/all/modules/jquery_update/replace/ui/themes/base/minified/jquery.ui.core.min.css'])) {
    unset($css['sites/all/modules/jquery_update/replace/ui/themes/base/minified/jquery.ui.core.min.css']);
  }
 //dpm($css);

//  unset($css[drupal_get_path('module', 'views') . '/css/views.css']);
}

/**
* Send an HTTP request to a the $url and check the header posted back.
*
* @param $url String url to which we must send the request.
* @param $failCodeList Int array list of code for which the page is considered invalid.
*
* @return status and header info
*/
function isUrlExists($url, array $failCodeList = array(404)){

    $exists = false;
//		$proto = '((https?|ftp)\:\/\/)?';
//			preg_match("/^$proto/", $url, $matches);
	//	if (pre_match('

			$regex = "((https?|ftp)\:\/\/)?"; // Scheme
			$regex .= "([a-z0-9+!*(),;?&=\$_.-]+(\:[a-z0-9+!*(),;?&=\$_.-]+)?@)?"; // User and Pass
			$regex .= "([a-z0-9-.]*)\.([a-z]{2,3})"; // Host or IP
			$regex .= "(\:[0-9]{2,5})?"; // Port
			$regex .= "(\/([a-z0-9+\$_-]\.?)+)*\/?"; // Path
			$regex .= "(\?[a-z+&\$_.-][a-z0-9;:@&%=+\/\$_.-]*)?"; // GET Query
			$regex .= "(#[a-z_.-][a-z0-9+\$_.-]*)?"; // Anchor
			$headers = FALSE;
			if (preg_match("/^$regex/", $url)) {
        $handle = curl_init($url);


        curl_setopt($handle, CURLOPT_RETURNTRANSFER, true);

        curl_setopt($handle, CURLOPT_SSL_VERIFYPEER, false);

        curl_setopt($handle, CURLOPT_HEADER, true);

        curl_setopt($handle, CURLOPT_NOBODY, true);

        curl_setopt($handle, CURLOPT_USERAGENT, true);


        $headers = curl_exec($handle);

        curl_close($handle);


        if (empty($failCodeList) or !is_array($failCodeList)){

            $failCodeList = array(404); 
        }

        if (!empty($headers)){

            $exists = true;

            $headers = explode(PHP_EOL, $headers);
            foreach($failCodeList as $code){

                if (is_numeric($code) and strpos($headers[0], strval($code)) !== false){

                    $exists = false;

                    break;  
                }
            }
        }
    }

    return array(
			'status' => $exists,
			'header' => $headers
			);
}

function si_baseline_page_alter(&$page) {
  $page['colorbox'] = FALSE;
  $params = drupal_get_query_parameters();
  if (isset($params['iframe']) || arg(0) == 'tableau') {
    $page['colorbox'] = TRUE;
  }
}