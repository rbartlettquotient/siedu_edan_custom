<?php
function si_baseline_breadcrumb($variables) {
	$breadcrumb = $variables['breadcrumb'];
	$out = '';
 	if (!empty($breadcrumb)) {
  	$breadcrumb[] = drupal_get_title();
    $out = '<ul class="breadcrumbs">';
		$count = count($breadcrumb)-1;
		foreach($breadcrumb as $i => $value) {
				$crumb = '<span>' . $value . '</span>';
      	$out .= $i == $count ? '<li class="active">'.$crumb.'</li>' : '<li>'.$crumb.'</li>';
    	}
      $out .= '</ul>';
    }
      return $out;

}
