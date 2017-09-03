<?php

if(module_exists('devel') && isset($_GET['dpm']) && user_access('access devel information')){
  dpm($variables);
}

elseif (isset($_GET['dump'])) {
  var_export($variables['docs']);
}
$query = array(
  'width' => '85%',
  'height' => '85%',
  'iframe' => 'true',
  'destination' => $destination
);
?>
<?php if($buttons): ?>
<div class="wrapper--btn">
  <div class="explore-buttons l-container-wide ">
    <ul class="five">
      <?php foreach ($buttons as $button): ?>
        <li><?php print $button; ?></li>
      <?php endforeach; ?>
    </ul>

    </div>
  </div>

<?php endif; ?>
<div class="exhibitions-wrapper search-wrapper l-container-wide <?php print $facets ? 'exhibtions-page expanded' : 'block'; ?>">
  <?php if ($facets): ?>

  <div class="filter-wrapper default">


      <?php echo $facets; ?>


  </div>
  <?php endif; ?>
  <?php if (!empty($docs)): ?>
  <div class="search-results-wrapper">
    <div id="search-<?php print $id; ?>" class="<?php print $container_class ?>">
      <ul id="exhibit-list" class="reset-list content search-results exhbition-search" >
        <?php foreach ($docs as $i => $doc): ?>
          <li <?php echo drupal_attributes($doc['row_attributes']); ?>>
            <a href="<?php echo url($doc['#record_link'], array('query' => $query)); ?>" class="card card--exhibit colorbox-load">
              <?php if (isset($doc['rendered_image']) && !empty($doc['rendered_image'])): ?>
                <figure>
                  <?php echo $doc['rendered_image']; ?>
                </figure>
              <?php endif; ?>

              <div class="b-text-wrapper">
                <h2 class="name epsilon"><?php echo $doc['title']; ?></h2>
                <p class="metatag">
                  <?php echo $doc['#status_tag']; ?>
                  <span class="date"><?php echo $doc['#short_date']?></span>

                  <?php echo $doc['#formatted_location']; ?>
                </p>
              </div>
            </a>
          </li>
        <?php endforeach; ?>
      </ul>
      <div id="placeholder"></div>
      <?php echo $pager; ?>
    </div>
  </div>
   <?php else: ?>
    <p><?php print $empty_msg; ?></p>
  <?php endif; ?>
</div>

