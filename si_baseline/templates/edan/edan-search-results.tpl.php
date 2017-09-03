
<?php

if(module_exists('devel') && isset($_GET['dpm-edan']) && user_access('access devel information')){
  dpm($variables);
}

elseif (isset($_GET['dump'])) {
  var_export($variables);
}  ?>

<?php 
/**
 * Theme Edan Search Results
 */ 
?>


<div class="edan-search clearfix <?php print variable_get('si_edan_default', 'list-view'); ?>">

  <?php if ($tabs): ?>
  <div class="edan-search-tabs">
    <?php print($tabs); ?>
  </div>
  <?php endif; ?>


  <div class="edan-results-summary">
		<p><?php print($results_summary); ?></p>
    <?php print $pager; ?>
  </div>  
  
  <div id="search-<?php print $id; ?>" class="grid grid-wrapper  search-results-container <?php print $container_class; ?>">
    <ul class="search-results <?php print $results_class; ?> content">
      <?php foreach ($docs as $doc): ?>


      <li class="grid-item" <?php print drupal_attributes($doc['row_attributes']); ?>>
        <div class="edan-row">
              
              <?php
              $img_uri = '';
              if (strpos($doc['content']['descriptiveNonRepeating']['online_media']['media'][0]['thumbnail'], 'ids.si.edu') !== false) :
                $img_uri = $doc['content']['descriptiveNonRepeating']['online_media']['media'][0]['thumbnail']."&max_w=400";
                else :
                $img_uri = "https://ids.si.edu/ids/deliveryService?id=".$doc['content']['descriptiveNonRepeating']['online_media']['media'][0]['thumbnail']."&max_w=400";
              endif; ?>

          <?php if (isset($_GET['dump'])): ?>
          	<h3 class="title"><?php echo $doc['#title']; ?></h3> 
						<--!
						<?php print '<pre>' . var_export($doc, TRUE) . '</pre>';  
							else: ?>

						<?php 
            
            if (isset($doc['content']['descriptiveNonRepeating']['online_media']['media'])): ?>


              <div class="record-media">
                <?php if(isset($doc['#title_link']) && !empty($doc['#title_link'])):
                  $url = url($doc['#title_link']['path'], array('query' => $doc['#title_link']['query'], 'fragment' => $doc['#title_link']['fragment']));
                  ?>

                  <a href="<?php print $url;?>" title="Thumbnail image for <?php print $doc['#title_plain']; ?>">
                    <img src="<?php echo $img_uri; ?> " alt="<?php print $doc['#title_plain']; ?>" />
                  </a>
                <?php else: ?>
                    <img src="<?php echo $img_uri; ?> " alt="<?php print $doc['#title_plain']; ?>" />
                <?php endif; ?>          	
              </div>
            <?php endif; ?>
            <div class="record-details<?php print isset($doc['content']['descriptiveNonRepeating']['online_media']['media']) ? ' has-thumbnail' : ''; ?>"
              style="padding:0 5px 5px 5px;">
              <div class="title"><?php echo $doc['#title']; ?></div> 
              
              <?php foreach ($doc['content']['freetext'] as $field => $vals): ?>
                <dl class="edan-search-<?php echo $field; ?>">
                  <?php $current_label = ''; ?>
                  <?php foreach ($vals as $value): ?>
                    <?php if ($value['label'] != $current_label): ?>
                  <dt><?php echo $value['label']; ?></dt><?php $current_label = $value['label']; ?>
                    <?php endif; ?>
                  <dd><?php echo $value['content']; ?></dd>
                  <?php endforeach; ?>
                </dl>
              <?php endforeach; ?>
            
            </div>
          <?php endif; ?>
        </div>
      </li>
      

      <?php endforeach; ?>



    </ul>
    <?php if ($facets): ?>
      <div class="edan-search-facets">
        <?php echo $facets; ?>
      </div>
    <?php endif; ?>

    <?php echo $pager; ?>
  </div>


</div>