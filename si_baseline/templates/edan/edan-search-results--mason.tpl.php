<?php
  if(module_exists('devel') && isset($_GET['dpm-edan']) && user_access('access devel information')) {
    dpm($variables);
}
/**
 * Theme Edan Search Results
 */
?>


  <div id="search-<?php print $id; ?>" class="masonry-grid-wrapper search-results-container">
    <ul class="<?php print $results_class; ?>">
      <?php foreach ($docs as $doc): ?>


      <li <?php print drupal_attributes($doc['row_attributes']); ?>>
            <div class="node--teaser node--teaser-long">

              <a href="<?php echo $doc['#title_link']['rendered_path'] ?>" class="inner<?php echo $colorbox ? ' colorbox-load' : '' ?>">

                <?php if (isset($doc['rendered_image']) && !empty($doc['rendered_image'])):
                  print $doc['rendered_image'];
                  elseif (isset($doc['content']['descriptiveNonRepeating']['online_media']['media'])): ?>
                  <div class="b-media-wrapper field--type-image">
                    <?php print $doc['rendered_image']; ?>
                  </div>
                <?php endif; ?>
                <div class="b-text-wrapper">
                  <?php if(isset($doc['preface'])): ?>
                    <div class="preface">
                      <?php print $doc['preface']; ?>
                    </div>
                  <?php endif; ?>
                    <h3 class="title delta"><?php echo $doc['#title_plain']; ?></h3>
                </div>
              </a>
            </div>

      </li>
      

      <?php endforeach; ?>



    </ul>

    <?php if ($pager): ?>
      <div id="placeholder"></div>
      <?php print $pager; ?>


    <?php endif; ?>
</div>

